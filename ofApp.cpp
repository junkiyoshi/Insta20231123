#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetColor(255);

	ofEnableDepthTest();
	ofSetLineWidth(1);

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->line.clear();

	auto noise_param = glm::vec3(ofRandom(360), ofRandom(360), ofRandom(360));

	for (int radius = 50; radius <= 300; radius += 5) {

		int start_index = this->line.getNumVertices();
		int index = start_index;

		auto z = ofMap(ofNoise(radius * 0.005 + ofGetFrameNum() * 0.03), 0, 1, -300, 300);
		for (int deg = 0; deg < 360; deg += 1) {

			auto vertex = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z);
			this->line.addVertex(vertex);

			if (deg > 0) {

				this->line.addIndex(index - 1);
				this->line.addIndex(index);
			}

			index++;
		}

		this->line.addIndex(this->line.getNumVertices() - 1);
		this->line.addIndex(start_index);
	}

	int index_span = 30;
	for (int index = 0; index < this->line.getNumVertices() - 360; index += index_span) {

		this->line.addIndex(index);
		this->line.addIndex(index + 360);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(115);
	ofRotateZ(ofGetFrameNum() * 1.44);
	

	this->line.drawWireframe();

	this->cam.end();

	/*
	int start = 150;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}