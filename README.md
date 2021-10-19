# blaast-template-base

Welcome to your new [Blaast] app!

* Deployment URL: <https://blaast-template-base.shopifyfaas.com>
* ShipIt Stack: <https://shipit.shopify.io/shopify/blaast-template-base/production>
* Shopify Build Pipeline: <https://buildkite.com/shopify/blaast-template-base-ci>

Here's a summary of the most important things you need to get started. For more information see the [Blaast]
documentation.

## Getting Started

Blaast projects contain handlers defined in _lib/handlers which handle incoming HTTP, [JSON-RPC], or [CloudEvent]
requests. Each of these handlers defines one or more _functions_ which are mapped to paths in case of HTTP, or the
`method` parameter for JSON-RPC.

This template ships with a sample handler (_root.rb_) which defines a simple Hello world function, so you can get an idea
of what handlers and functions look like.

* Run a local server: `dev s`
* Run unit tests: `dev test [FILE_NAME]`
* Run lint (rubocop): `dev lint`

## Writing Handlers

Handlers in [Blaast] are classes in _lib/handlers/_ that have mixed in the `Blaast::Handler` module. This module
is responsible for making your functions available at runtime and ensuring that `current_user`, `logger`, `params`,
`secrets`, etc. are available in your functions.

> Functions, similar to Rails actions, consist of all non-inherited public methods defined in a handler.

URLs (and method names for JSON-RPC) are deterministically generated based on the full signature of the function. For
example, if we have the following handler:

```ruby
# lib/handlers/api.rb
module Handlers
  class API
    include Blaast::Handler

    def version
      '1.0'
    end
  end
end
```

The `version` function will be available at <https://blaast-template-base.shopifyfaas.com/api/version> or via the
`api.version` method for JSON-RPC calls.

While there's no support for changing method names in paths (in this case `version`) we do have support for setting a
custom namespace to be used. If we'd like this function to be available at `/api/v1/version` we'd need to add a call to
the `namespace` method after including `Blaast::Handler`:

```ruby
module Handlers
  class API
    include Blaast::Handler

    namespace('/api/v1')
    ...
    ...
  end
end
```

This could also be accomplished by moving this function to `Handlers::API::V1#version`. Dealer's choice.

### Parameters

Inside your functions, request parameters are available to you via the `params` object. This is a string-keyed hash (not
symbols) which contains the parameters for the function call. We've worked hard to make sure you don't need to worry
about which protocol (HTTP, JSON-RPC, CloudEvents) is being used when writting functions, it just does the right thing.
`params` takes on different values depending on the protocol and HTTP method:

* HTTP GET: The params from the Rack request
* HTTP POST: If content type is _application/json_, the parsed body of the request, otherwise same as GET
* JSON-RPC: The `params` hash included in the call
* CloudEvent: The `data` from the decoded event (from the body)

### Secrets

Secrets are available via the aptly named `secrets` hash. Any key under `environment` in
_config/secrets.production-unrestricted.ejson_ will be available at runtime. For example:

```ruby
module Handlers
  class API
    include Blaast::Handler

    def make_the_call
      token = secrets.fetch('MY_API_TOKEN')
      ...
    end
  end
end
```

### Testing Your Handlers

[Blaast] ships with a helper; `Blaast::Testing` which can be included in your tests to make unit testing a breeze. Check
out _test/handlers/root_test.rb_ for examples on how to use it.

If you'd like to run some manual testing locally, by using `curl` for example, or testing out the JSON-RPC invoker, here
are some examples of how to do that:

* HTTP GET: `curl http://localhost:8080/` or `curl http://localhost:8080/?target=Tester`
* HTTP POST: `curl -X POST -d '{"target":"Tester"}' -H 'Content-Type: application/json' http://localhost:8080`
* JSON-RPC: `bundle exec blaast invoke http://localhost:8080 --method . --params target=Tester`

If auth is enabled for your project (details below), you'll need to supply credentials for the call:

* `curl -H "Authorization: Bearer $(gcloud auth print-identity-token)" http://localhost:8080`
* `bundle exec blaast invoke http://localhost:8080 --auth --method . --params target=Tester`

## Deploying Your Project

When this project was initialized, we took care of setting up a [Shopify Build] pipeline and [ShipIt] stack for you. The
ShipIt stack is already configured with continuous deployment enabled. This means, on every merge to _master_, your
project will be deployed.


You can see the deployment status with `bundle exec blaast status`, including the most recent time from commit to
deployed.

## Managing Secrets

Secrets are managed via EJSON as usual. The main difference for Blaast projects is that these secrets are synchornized
with the [Google Secret Manager] on each deploy making them available to your functions at runtime without requiring the
private key to be embedded/loaded into the container.

You can securely add secrets to your project by executing the following:

    echo -n "SUPER DUPER SECRET" | bundle exec blaast secret set MY_SECRET

This will write the secret to the `environment.MY_SECRET` key to the ejson within the `config` directory. On the next
deploy, the secret will be synchronized making `secrets.fetch('MY_SECRET')` available to your functions.

See `bundle exec blaast secrets -h` for more options.

## Authentication

Authentication in Blaast is at the project level, meaning you cannot have one function require auth and another not in
the same project. Without authentication, anyone in the world can invoke your function.

To enable authentication:

    bundle exec blaast auth enable

Then deploy your project.

To check authentication status:

    bundle exec blaast auth check

Authenticated requests must pass a bearer token in the Authorization header containing the gcloud identity of the caller.

Anyone in RnD at Shopify can call functions. Similarly, the service account used to run functions can call any other
functions, allowing the ability to compose functions from already deployed ones (if that's your thing).

```bash
curl -H "Authorization: Bearer $(gcloud auth print-identity-token)" https://blaast-template-base.shopifyfaas.com
bundle exec blaast invoke https://blaast-template-base.shopifyfaas.com --auth
```

Or from code:

```ruby
invoker = Blaast::Invoker::JSONRPC.new('https://blaast-template-base.shopifyfaas.com', authorization: 'gcloud')
invoker.invoke(:post, target: 'Tester')
```

> If you need a machine account to be able to access your application, ensure that it has roles/run.invoker IAM
> permissions.

# Logs

Logs are available right from your terminal via:

* `bundle exec blaast logs`
* `bundle exec blaast logs --since=1h --stream=stderr`

Similar to Rails, functions can write logs via the `logger` object. (i.e. `logger.warn('...')`).

[Blaast]: https://github.com/Shopify/blaast
[CloudEvent]: https://cloudevents.io
[Google Secret Manager]: https://cloud.google.com/secret-manager
[JSON-RPC]: https://www.jsonrpc.org/specification
[ShipIt]: https://github.com/Shopify/shipit-engine#shipit---documentation
[Shopify Build]: https://shopify-build.docs.shopify.io/
