require 'home_tram_schedules_webapp'
require 'rack/test'

RSpec.describe HomeTramSchedulesWebapp do
  include Rack::Test::Methods

  def app
    HomeTramSchedulesWebapp
  end


  describe 'root path' do
    subject { get '/' }

    it 'works' do
      subject

      expect(last_response.status).to eq(200)
      expect(JSON.parse(last_response.body)).to eq({ 'status' => 'ok' })
    end
  end

  describe 'stops path' do
    subject { get '/stops/whatever' }

    let(:payload) do
      [
        {
          'lol' => 'oki'
        }
      ]
    end

    before do
      allow(NextTramSchedulesApi).to receive(:new).and_call_original
      allow_any_instance_of(NextTramSchedulesApi).to receive(:perform).and_return(payload)
    end

    it 'works' do
      subject

      expect(last_response.status).to eq(200)
      expect(JSON.parse(last_response.body)).to eq(payload)
    end

    it 'instanciate NextTramSchedulesApi with uid' do
      expect(NextTramSchedulesApi).to receive(:new).with('whatever')

      subject
    end
  end
end
