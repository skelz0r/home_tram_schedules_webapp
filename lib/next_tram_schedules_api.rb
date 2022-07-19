# frozen_string_literal: true

require 'excon'
require 'json'

class NextTramSchedulesApi
  attr_reader :arret_id

  def initialize(arret_id)
    @arret_id = arret_id
  end

  def perform
    response = make_http_call

    format(response)
  end

  private

  def make_http_call
    connection = Excon.new(next_tram_schedules_endpoint, omit_default_port: true)
    connection.get(
      headers: {
        'Accept' => 'application/json'
      },
      query: {
        key: api_key,
        attributes: [
          'libelle',
          'hor_app',
          'hor_theo',
          'hor_estime',
          'terminus',
        ].to_json,
        datainputs: {
          arret_id: arret_id
        }.to_json
      }
    )
  end

  def format(response)
    data = JSON.parse(response.body)['features']

    data.map do |datum|
      attributes = datum['properties']

      {
        terminus: attributes['terminus'],
        schedule: {
          estimated: attributes['hor_estime'],
          theorical: attributes['hor_theo'],
          applicable: attributes['hor_app']
        }
      }
    end
  end

  def next_tram_schedules_endpoint
    'https://data.bordeaux-metropole.fr/geojson/process/saeiv_arret_passages'
  end

  def api_key
    ENV.fetch('BORDEAUX_API_KEY')
  end
end
