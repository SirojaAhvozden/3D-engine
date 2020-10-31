#include "Skeleton.h"
#include "Texture.h"
#include <iostream>
#include "Mesh.h"

std::vector<Bone*>* Skeleton::getBones() {
	return &bones;
}

Skeleton::Skeleton(glm::vec3 pos, glm::vec3 angle, Object* parent) 
	: Actor(pos, angle, parent) {

	animStatys = 1;
	poseIndex = 0;
	deltaTime = 0;

	GLuint Tex;
	if (getTexture(&Tex, "head.png", IL_PNG) != 0) {
		std::cout << "Couldn't open file" << std::endl;
		Tex = 0;
	}
	Mesh* mesh;

	bones.push_back(new Bone(this, NULL, glm::vec3(0, 4, 0), /*angle*/glm::vec3(0)));
	mesh = new Mesh(/*offest*/glm::vec3(-0.5, 0, -1.0001), glm::vec3(0), bones.back());
	setCube(mesh, /*sides*/glm::vec3(1, 0.5, 2.0002), /*color*/glm::vec3(0, 64, 0));

	bones.push_back(new Bone(this, bones[0], glm::vec3(0, 0, -0.5), /*angle*/glm::vec3(0)));
	mesh = new Mesh(/*offest*/glm::vec3(-0.505, -2, -0.505), glm::vec3(0), bones.back());
	setCube(mesh, /*sides*/glm::vec3(1.01, 2, 1.01), /*color*/glm::vec3(0, 64, 0));

	bones.push_back(new Bone(this, bones[0], glm::vec3(0, 0, 0.5), /*angle*/glm::vec3(0)));
	mesh = new Mesh(/*offest*/glm::vec3(-0.505, -2, -0.505), glm::vec3(0), bones.back());
	setCube(mesh, /*sides*/glm::vec3(1.01, 2, 1.01), /*color*/glm::vec3(0, 64, 0));

	bones.push_back(new Bone(this, bones[1], glm::vec3(0, -2, 0), /*angle*/glm::vec3(0)));
	mesh = new Mesh(/*offest*/glm::vec3(-0.5,-2,-0.5), glm::vec3(0), bones.back());
	setCube(mesh, /*sides*/glm::vec3(1, 2, 1), /*color*/glm::vec3(244, 205, 138));

	bones.push_back(new Bone(this, bones[2], glm::vec3(0, -2, 0), /*angle*/glm::vec3(0)));
	mesh = new Mesh(/*offest*/glm::vec3(-0.5, -2, -0.5), glm::vec3(0), bones.back());
	setCube(mesh, /*sides*/glm::vec3(1, 2, 1), /*color*/glm::vec3(244, 205, 138));

	bones.push_back(new Bone(this, bones[0], glm::vec3(0, 0.5, 0), /*angle*/glm::vec3(0)));
	mesh = new Mesh(/*offest*/glm::vec3(-0.5, 0, -1), glm::vec3(0), bones.back());
	setCube(mesh, /*sides*/glm::vec3(1, 3, 2), /*color*/glm::vec3(40, 40, 40));

	bones.push_back(new Bone(this, bones[5], glm::vec3(0, 2.5, 1.5), /*angle*/glm::vec3(0)));
	mesh = new Mesh(/*offest*/glm::vec3(-0.5005, -2 + 0.5, -0.5005), glm::vec3(0), bones.back());
	setCube(mesh, /*sides*/glm::vec3(1.001, 2, 1.001), /*color*/glm::vec3(40, 40, 40));

	bones.push_back(new Bone(this, bones[5], glm::vec3(0, 2.5, -1.5), /*angle*/glm::vec3(0)));
	mesh = new Mesh(/*offest*/glm::vec3(-0.5005, -2 + 0.5, -0.5005), glm::vec3(0), bones.back());
	setCube(mesh, /*sides*/glm::vec3(1.001, 2, 1.001), /*color*/glm::vec3(40, 40, 40));

	bones.push_back(new Bone(this, bones[6], glm::vec3(0, -1.5, 0), /*angle*/glm::vec3(0)));
	mesh = new Mesh(/*offest*/glm::vec3(-0.5, -2, -0.5), glm::vec3(0), bones.back());
	setCube(mesh, /*sides*/glm::vec3(1, 2, 1), /*color*/glm::vec3(244, 205, 138));

	bones.push_back(new Bone(this, bones[7], glm::vec3(0, -1.5, 0), /*angle*/glm::vec3(0)));
	mesh = new Mesh(/*offest*/glm::vec3(-0.5, -2, -0.5), glm::vec3(0), bones.back());
	setCube(mesh, /*sides*/glm::vec3(1, 2, 1), /*color*/glm::vec3(244, 205, 138));

	bones.push_back(new Bone(this, bones[5], glm::vec3(0, 3, 0), /*angle*/glm::vec3(0)));
	mesh = new Mesh(/*offest*/glm::vec3(-0.75, 0, -0.75), glm::vec3(0), bones.back());
	setCube(mesh, /*sides*/glm::vec3(1.5, 1.5, 1.5), /*color*/glm::vec3(255, 255, 255), Tex);

	Animation anim;
	
	AnimationPoseBones bones;
// animation 0(stand pose)
	// pose
		bones.time = 1;
		bones.bone.assign(this->bones.size(), AnimationBoneTransform());

		bones.bone[0].setRot(glm::vec3(0, -30, 0));
		bones.bone[1].setRot(glm::vec3(15, 30, 30));
		bones.bone[2].setRot(glm::vec3(-15, -30, 20));
		bones.bone[3].setRot(glm::vec3(0, 0, -30));
		bones.bone[4].setRot(glm::vec3(0, 0, -40));
		bones.bone[5].setRot(glm::vec3(0, 15, -6));

		bones.bone[10].setRot(glm::vec3(0, 15, 0));

		anim.pose.push_back(bones);

	animPatterns.push_back(anim);
	anim.pose.clear();
// animation 1
	// pose 1
		bones.time = 2;
		bones.bone.assign(this->bones.size(), AnimationBoneTransform());

		anim.pose.push_back(bones);
	// pose 2
		bones.time = 1;
		bones.bone.assign(this->bones.size(), AnimationBoneTransform());

		bones.bone[1].setRot(glm::vec3(0, 0, 45));
		bones.bone[2].setRot(glm::vec3(0, 0, -45));
		bones.bone[3].setRot(glm::vec3(0, 0, -45));
		bones.bone[4].setRot(glm::vec3(0, 0, -45));

		anim.pose.push_back(bones);
	// pose 3
		bones.time = 1;
		bones.bone.assign(this->bones.size(), AnimationBoneTransform());

		bones.bone[1].setRot(glm::vec3(0, 0, 23));
		bones.bone[2].setRot(glm::vec3(0, 0, -30));
		bones.bone[3].setRot(glm::vec3(0, 0, -23));
		bones.bone[4].setRot(glm::vec3(0, 0, -60));

		anim.pose.push_back(bones);
	// pose 4
		bones.time = 2;
		bones.bone.assign(this->bones.size(), AnimationBoneTransform());

		anim.pose.push_back(bones);
	// pose 5
		bones.time = 1;
		bones.bone.assign(this->bones.size(), AnimationBoneTransform());

		bones.bone[1].setRot(glm::vec3(0, 0, -45));
		bones.bone[2].setRot(glm::vec3(0, 0, 45));
		bones.bone[3].setRot(glm::vec3(0, 0, -45));
		bones.bone[4].setRot(glm::vec3(0, 0, -45));

		anim.pose.push_back(bones);
	// pose 6
		bones.time = 1;
		bones.bone.assign(this->bones.size(), AnimationBoneTransform());

		bones.bone[1].setRot(glm::vec3(0, 0, -30));
		bones.bone[2].setRot(glm::vec3(0, 0, 23));
		bones.bone[3].setRot(glm::vec3(0, 0, -60));
		bones.bone[4].setRot(glm::vec3(0, 0, -23));

		anim.pose.push_back(bones);


	animPatterns.push_back(anim);
	anim.pose.clear();

	bones.time = 1;
	bones.bone.assign(this->bones.size(), AnimationBoneTransform());
	//bones.bone[10].setRot(glm::vec3(0, 15, 0));

	anim.pose.push_back(bones);

	animPatterns.push_back(anim);
	anim.pose.clear();

}

glm::mat4 Skeleton::getAnimationMatrix(int boneID) {

	AnimationBoneTransform transform;

	float k = deltaTime / animPatterns[animStatys].pose[poseIndex].time;

	//std::cout << k << std::endl;

	if (k >= 1.f) {
		deltaTime -= animPatterns[animStatys].pose[poseIndex].time;

		poseIndex++;
		if (poseIndex > animPatterns[animStatys].pose.size() - 1) {
			poseIndex = 0;
		}

		k = deltaTime / animPatterns[animStatys].pose[poseIndex].time;
	}

	int nextPoseIndex = poseIndex + 1;
	if (nextPoseIndex > animPatterns[animStatys].pose.size() - 1) {
		nextPoseIndex = 0;
	}

	transform.transform = animPatterns[animStatys].pose[poseIndex].bone[boneID].transform + 
		+ k * (animPatterns[animStatys].pose[nextPoseIndex].bone[boneID].transform - animPatterns[animStatys].pose[poseIndex].bone[boneID].transform);

	transform.rotation = animPatterns[animStatys].pose[poseIndex].bone[boneID].rotation +
		+ k * (animPatterns[animStatys].pose[nextPoseIndex].bone[boneID].rotation - animPatterns[animStatys].pose[poseIndex].bone[boneID].rotation);

	glm::mat4 r = glm::mat4_cast(glm::quat(transform.rotation));
	glm::mat4 t(1.f);
	t = glm::translate(t, transform.transform);

	//return glm::scale(t * r, glm::vec3(0.5));
	return t * r;
}
