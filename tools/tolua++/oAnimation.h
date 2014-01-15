class oFrameAction : public CCFiniteTimeAction
{
	void setLoop(bool loop);
	static oFrameAction* create(const char* filename);
};
