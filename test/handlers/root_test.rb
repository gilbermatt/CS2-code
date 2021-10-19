# frozen_string_literal: true

require 'test_helper'

module Handlers
  class RootTest < Minitest::Test
    include Blaast::Testing

    # This file is for demonstration purposes. In a typical scenario you won't need to test your functions with each
    # protocol (http, cloud events, and RPC) since Blaast does this for you. We've added tests for each of them simply
    # to show how it's done.

    def test_get_default
      with_blaast_server do
        resp = http_get('/')
        assert(resp.successful?)
        assert_equal('Hello world!', resp.body.join)

        resp = http_get('/?target=Bob')
        assert(resp.successful?)
        assert_equal('Hello Bob!', resp.body.join)
      end
    end

    def test_post_default
      with_blaast_server do
        {
          '' => 'Hello world!',
          JSON.generate(target: 'Bob') => 'Hello Bob!'
        }.each do |body, result|
          resp = http_post('/', body, ['Content-Type: application/json'])

          assert(resp.successful?)
          assert_equal(result, resp.body.join)
        end
      end
    end

    def test_cloud_event
      with_blaast_server do
        resp = emit_event('/')
        assert(resp.successful?)
        assert_equal('Hello world!', resp.body.join)

        resp = emit_event('/', target: 'Bob')
        assert(resp.successful?)
        assert_equal('Hello Bob!', resp.body.join)
      end
    end

    def test_rpc_call
      with_blaast_server do
        result, code = exec_rpc('default')
        assert(code.zero?)
        assert_equal('Hello world!', result)

        result, code = exec_rpc('', target: 'Bob')
        assert(code.zero?)
        assert_equal('Hello Bob!', result)
      end
    end
  end
end
