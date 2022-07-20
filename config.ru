require 'dotenv/load'
require 'home_tram_schedules_webapp'
require 'rack/cors'

use Rack::Cors do
  allow do
    origins '*'
    resource '*', headers: :any, methods: [:get, :post, :options, :put]
  end
end

run HomeTramSchedulesWebapp
