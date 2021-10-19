# frozen_string_literal: true

require 'simplecov'
SimpleCov.start

$LOAD_PATH.unshift File.expand_path('../lib', __dir__)
ENV['TESTING'] = 'true'

require 'blaast'
require 'minitest/autorun'
require 'minitest/pride'
require 'mocha/minitest'
require 'pry-byebug'
require 'securerandom'
