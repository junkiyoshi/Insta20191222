#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face_mesh.clear();
	this->frame_mesh.clear();

	int radius_span = 10;
	int deg_span = 8;
	for (int radius = 100; radius < 300; radius += radius_span * 4) {

		for (int deg_start = 0; deg_start < 360; deg_start += deg_span) {

			auto noise_seed = glm::vec2((300 - radius) * cos(deg_start * DEG_TO_RAD), (300 - radius) * sin(deg_start * DEG_TO_RAD));
			auto noise_value = ofNoise(glm::vec3(noise_seed * 0.01, ofGetFrameNum() * 0.005));
			auto z = ofMap(noise_value, 0, 1, -radius, radius);
			int param_index = this->face_mesh.getNumVertices();
			for (int deg = deg_start; deg < deg_start + deg_span; deg++) {

				int index = this->face_mesh.getNumVertices();

				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), z));
				vertices.push_back(glm::vec3((radius + radius_span) * cos(deg * DEG_TO_RAD), (radius + radius_span) * sin(deg * DEG_TO_RAD), z));
				vertices.push_back(glm::vec3((radius + radius_span) * cos((deg + 1) * DEG_TO_RAD), (radius + radius_span) * sin((deg + 1) * DEG_TO_RAD), z));
				vertices.push_back(glm::vec3(radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), z));

				vertices.push_back(glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
				vertices.push_back(glm::vec3((radius + radius_span) * cos(deg * DEG_TO_RAD), (radius + radius_span) * sin(deg * DEG_TO_RAD), 0));
				vertices.push_back(glm::vec3((radius + radius_span) * cos((deg + 1) * DEG_TO_RAD), (radius + radius_span) * sin((deg + 1) * DEG_TO_RAD), 0));
				vertices.push_back(glm::vec3(radius * cos((deg + 1) * DEG_TO_RAD), radius * sin((deg + 1) * DEG_TO_RAD), 0));

				this->face_mesh.addVertices(vertices);

				this->face_mesh.addIndex(index + 0);	this->face_mesh.addIndex(index + 1); this->face_mesh.addIndex(index + 2);
				this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 3);

				this->face_mesh.addIndex(index + 4);	this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 6);
				this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 6); this->face_mesh.addIndex(index + 7);

				this->face_mesh.addIndex(index + 0);	this->face_mesh.addIndex(index + 3); this->face_mesh.addIndex(index + 7);
				this->face_mesh.addIndex(index + 0); this->face_mesh.addIndex(index + 4); this->face_mesh.addIndex(index + 7);

				this->face_mesh.addIndex(index + 1);	this->face_mesh.addIndex(index + 2); this->face_mesh.addIndex(index + 6);
				this->face_mesh.addIndex(index + 1);	this->face_mesh.addIndex(index + 5); this->face_mesh.addIndex(index + 6);

				this->frame_mesh.addVertices(vertices);

				this->frame_mesh.addIndex(index + 0); this->frame_mesh.addIndex(index + 3);
				this->frame_mesh.addIndex(index + 4); this->frame_mesh.addIndex(index + 7);

				this->frame_mesh.addIndex(index + 1); this->frame_mesh.addIndex(index + 2);
				this->frame_mesh.addIndex(index + 5); this->frame_mesh.addIndex(index + 6);
			}

			this->face_mesh.addIndex(param_index + 0); this->face_mesh.addIndex(param_index + 1); this->face_mesh.addIndex(param_index + 5);
			this->face_mesh.addIndex(param_index + 0); this->face_mesh.addIndex(param_index + 4); this->face_mesh.addIndex(param_index + 5);

			this->frame_mesh.addIndex(param_index + 0); this->frame_mesh.addIndex(param_index + 1);
			this->frame_mesh.addIndex(param_index + 4); this->frame_mesh.addIndex(param_index + 5);

			this->frame_mesh.addIndex(param_index + 0); this->frame_mesh.addIndex(param_index + 4);
			this->frame_mesh.addIndex(param_index + 1); this->frame_mesh.addIndex(param_index + 5);

			param_index = this->face_mesh.getNumVertices() - 8;

			this->face_mesh.addIndex(param_index + 2); this->face_mesh.addIndex(param_index + 3); this->face_mesh.addIndex(param_index + 6);
			this->face_mesh.addIndex(param_index + 3); this->face_mesh.addIndex(param_index + 6); this->face_mesh.addIndex(param_index + 7);

			this->frame_mesh.addIndex(param_index + 2); this->frame_mesh.addIndex(param_index + 3);
			this->frame_mesh.addIndex(param_index + 6); this->frame_mesh.addIndex(param_index + 7);

			this->frame_mesh.addIndex(param_index + 2); this->frame_mesh.addIndex(param_index + 6);
			this->frame_mesh.addIndex(param_index + 3); this->frame_mesh.addIndex(param_index + 7);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateZ(ofGetFrameNum() * 0.5);

	ofSetColor(39);
	this->face_mesh.draw();

	ofSetColor(239);
	this->frame_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}