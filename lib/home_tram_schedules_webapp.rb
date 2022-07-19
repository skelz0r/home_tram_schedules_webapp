# frozen_string_literal: true

require 'grape'
require 'next_tram_schedules_api'

class HomeTramSchedulesWebapp < Grape::API
  format :json

  get '/' do
    NextTramSchedulesApi.new('T_HANGAR_R').perform
  end
end
