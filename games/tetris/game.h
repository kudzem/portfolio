#pragma once
#include <memory>

namespace kudzem_games {

class game_config {
private:
	virtual void set_default() = 0;

public:
	virtual void apply_user_settings() = 0;
	virtual ~game_config() {}
};

class game {
private:
	std::shared_ptr<game_config> cfg = nullptr;
protected:
	std::shared_ptr<game_config> get_cfg() { return cfg; }
public:
	virtual std::shared_ptr<game_config> init_cfg() = 0;
	void configure();
	virtual void visualize() = 0;
	virtual void interaction() = 0;
	virtual void logic() = 0;

	void launch();

	virtual ~game() {}
};


}