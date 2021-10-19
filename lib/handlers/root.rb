# frozen_string_literal: true

module Handlers
  class Root
    include Blaast::Handler

    namespace('')

    def default
      "Hello #{params.fetch('target', 'world')}!"
    end
  end
end
