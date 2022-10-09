#ifndef MOB_HPP
#define MOB_HPP

class Mob{
	public:
		virtual void move() = 0;
		virtual void render() = 0;
		virtual ~Mob() {};
};

#endif
