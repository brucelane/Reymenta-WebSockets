#include "ReymentaWebSocketsApp.h"

void ReymentaWebSocketsApp::prepareSettings(Settings* settings){
	settings->setFrameRate(12.0f);
	// parameters
	mParameterBag = ParameterBag::create();
	// utils
	mBatchass = Batchass::create(mParameterBag);
	// if AutoLayout, try to position the window on the 2nd screen
	if (mParameterBag->mAutoLayout)
	{
		mBatchass->getWindowsResolution();
	}

	settings->setWindowSize(mParameterBag->mRenderWidth, mParameterBag->mRenderHeight);
	settings->setWindowPos(Vec2i(mParameterBag->mRenderX, mParameterBag->mRenderY));
}

void ReymentaWebSocketsApp::setup()
{
	getWindow()->setTitle("Reymenta midi2osc");
	//getWindow()->connectClose(&ReymentaMidi2OSCApp::shutdown, this);
	ci::app::App::get()->getSignalShutdown().connect([&]() {
		ReymentaWebSocketsApp::shutdown();
	});
	// instanciate the OSC class
	mOSC = OSC::create(mParameterBag);
	// instanciate the WebSockets class
	mWebSockets = WebSockets::create(mParameterBag);
	mBatchass->setup();

	/*newLogMsg = false;

	// set ui window and io events callbacks
	ImGui::setWindow(getWindow());

	// midi
	setupMidi();
	if (mMidiIn.getNumPorts() > 0){
		mMidiIn.listPorts();
		mMidiIn.openPort(0);
		console() << "Opening MIDI port 0" << std::endl;
		mMidiIn.midiSignal.connect(boost::bind(&ReymentaWebSocketsApp::midiListener, this, boost::arg<1>::arg()));
	}else {
		console() << "No MIDI Ports found!!!!" << std::endl;
	}*/
}
void ReymentaWebSocketsApp::setupMidi()
{
	/*stringstream ss;
	newLogMsg = true;
	ss << "setupMidi: ";

	if (mMidiIn0.getNumPorts() > 0)
	{
		mMidiIn0.listPorts();
		for (int i = 0; i < mMidiIn0.getNumPorts(); i++)
		{

			midiInput mIn;
			mIn.portName = mMidiIn0.mPortNames[i];
			mMidiInputs.push_back(mIn);
			if (mParameterBag->mMIDIOpenAllInputPorts)
			{
				if (i == 0)
				{
					mMidiIn0.openPort(i);
					mMidiIn0.midiSignal.connect(boost::bind(&ReymentaWebSocketsApp::midiListener, this, boost::arg<1>::arg()));
				}
				if (i == 1)
				{
					mMidiIn1.openPort(i);
					mMidiIn1.midiSignal.connect(boost::bind(&ReymentaWebSocketsApp::midiListener, this, boost::arg<1>::arg()));
				}
				if (i == 2)				{
					mMidiIn2.openPort(i);
					mMidiIn2.midiSignal.connect(boost::bind(&ReymentaWebSocketsApp::midiListener, this, boost::arg<1>::arg()));
				}
				mMidiInputs[i].isConnected = true;
				ss << "Opening MIDI port " << i << " " << mMidiInputs[i].portName;
			}
			else
			{
				mMidiInputs[i].isConnected = false;
				ss << "Available MIDI port " << i << " " << mMidiIn0.mPortNames[i];
			}
		}
	}
	else
	{
		ss << "No MIDI Ports found!!!!" << std::endl;
	}
	ss << std::endl;
	mLogMsg = ss.str();*/
}
void ReymentaWebSocketsApp::midiListener(midi::Message msg){
  /*switch (msg.status)
  {
  case MIDI_NOTE_ON:
      notes[msg.pitch] = msg.velocity;
      status = "Pitch: " + toString(msg.pitch) + "\n" + 
          "Velocity: " + toString(msg.velocity);
      break;
  case MIDI_NOTE_OFF:
      break;
  case MIDI_CONTROL_CHANGE:
      cc[msg.control] = msg.value;
      status = "Control: " + toString(msg.control) + "\n" + 
          "Value: " + toString(msg.value);
      break;
  default:
      break;
  }*/

}
void ReymentaWebSocketsApp::update(){
	
}

void ReymentaWebSocketsApp::draw(){
	/*gl::clear(Color(0,0,0), true);
	gl::color(Color(1, 1, 1));
	gl::drawSolidRect(Rectf(Vec2f(0, 0), Vec2f(sliderValue * getWindowWidth(), getWindowHeight())));*/
}

//void ReymentaWebSocketsApp::processMidiMessage(midi::Message* message){
//	console() << "midi port: " << message->port << " ch: " << message->channel << " status: " << message->status;
//	console() << " byteOne: " << message->byteOne << " byteTwo: " << message->byteTwo << std::endl;
//	
//	switch (message->status) {
//		case MIDI_CONTROL_CHANGE:
//			if (message->byteOne == SLIDER_NOTE){
//				//sliderValue = message->byteTwo / 127.0f;
//			}
//			break;
//	}
//}

void ReymentaWebSocketsApp::keyDown(KeyEvent event)
{
	switch (event.getCode())
	{

	case ci::app::KeyEvent::KEY_ESCAPE:
		mParameterBag->save();
		//mBatchass->shutdownLoader();
		ImGui::Shutdown();
		mMidiIn0.closePort();
		mMidiIn1.closePort();
		mMidiIn2.closePort();
		quit();
		break;

	default:
		break;
	}
}

// This line tells Cinder to actually create the application
CINDER_APP_BASIC( ReymentaWebSocketsApp, RendererGl )
