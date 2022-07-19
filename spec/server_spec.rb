require 'home_tram_schedules_webapp'
require 'rack/test'

RSpec.describe HomeTramSchedulesWebapp do
  include Rack::Test::Methods

  def app
    HomeTramSchedulesWebapp
  end

  let(:payload) do
    [
      {
        'lol' => 'oki',
      }
    ]
  end

  before do
    allow_any_instance_of(NextTramSchedulesApi).to receive(:perform).and_return(payload)
  end

  it 'works' do
    get '/'

    expect(last_response.status).to eq(200)
    expect(JSON.parse(last_response.body)).to eq(payload)
  end
end
