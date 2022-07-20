# frozen_string_literal: true

require 'grape'
require 'next_tram_schedules_api'

class HomeTramSchedulesWebapp < Grape::API
  format :json

  helpers do
    def favorite_spots
      [
        {
          id: 'T_HANGAR_R',
          name: 'Les Hangars',
          direction: 'Pessac',
        },
        {
          id: 'T_HANGAR_A',
          name: 'Les Hangars',
          direction: 'Bacalan',
        }
      ]
    end
  end

  get '/' do
    {
      status: 'ok'
    }
  end

  get '/stops' do
    favorite_spots.map do |spot|
      spot.merge(
        url: "#{ENV.fetch('HOST')}/spots/#{spot[:id]}"
      )
    end
  end

  get '/stops/:uid' do
    NextTramSchedulesApi.new(params[:uid]).perform
  end
end
