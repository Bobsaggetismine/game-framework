
class robot_spawner : public bq::block{
	bq::animation animation;
	bq::entity* m_player = nullptr;
	bool m_fetched = false;
public:
	robot_spawner(float x, float y, float w, float h);
	void update() override;
	void render(bq::window&) override;
	void interact() override;
	void fetch_player();
};