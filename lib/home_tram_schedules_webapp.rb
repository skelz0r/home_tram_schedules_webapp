# frozen_string_literal: true

require 'grape'
require 'next_tram_schedules_api'

class HomeTramSchedulesWebapp < Grape::API
  format :json

  get '/' do
    {
      status: 'ok'
    }
  end

  get '/stops/:uid' do
    NextTramSchedulesApi.new(params[:uid]).perform
  end
end
