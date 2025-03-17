#pragma once
#include <memory>
#include <mutex>
#include <string>
#include <map>

namespace kudzem_games {

class game_config {
private:
	virtual void set_default() = 0;

public:
	virtual void apply_user_settings() = 0;
	virtual ~game_config() {}
};

class game {
protected:
	std::mutex _game_mtx;
	unsigned long _score = 0;
	unsigned long _record = 0;
	bool _stop = false;
	bool _paused = false;
	std::shared_ptr<game_config> cfg = nullptr;
	std::shared_ptr<game_config> get_cfg() { return cfg; }

	unsigned _timer_interval_ms = 800;
	unsigned _number_of_generated_obj = 0;
	unsigned _level = 0;
	unsigned _level_upgrade_counter = 10;

	void save_record();
	void read_record();

	const std::map<unsigned, unsigned> level2tmo = { {0, 800}, {1, 717}, {2, 633}, {3, 550}, {4, 467},
	{5, 383}, {6, 300}, {7, 217}, {8, 133}, {9, 100}, {10, 83},
	{15, 66}, {20, 50}, {30, 17}
   };

private:

public:
	virtual std::shared_ptr<game_config> init_cfg() = 0;
	void configure();
	virtual void visualize() = 0;
	virtual void interaction() = 0;
	virtual void logic() = 0;
	virtual void timer(int start_value) = 0;
	void stop() {
		_stop = true;
	}

	void pause() {
		_paused = !_paused;
	}

	virtual bool level_to_be_upgraded() = 0;
	void upgrade_level();

	void change_speed();

	void launch();

	virtual ~game() {}
};


}