#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <sksat/math/vector.hpp>
#include <sksat/math/gnuplot.hpp>

struct planet {
	sksat::math::vector<> pos, vel, acc;
	double m;
};

void time_step(std::vector<planet> &planet, const double &dt);
void save_prof(const std::vector<planet> &planet);

int main(int argc, char **argv){
	std::vector<planet> pl;
	const double dt = 0.001;
	const double max_time = 10.0;
	double t = 0.0;

	sksat::math::gnuplot plot;

	for(int i=0;i<3;i++)
		pl.push_back({});

	pl[0].pos.x	= 0.0;
	pl[0].pos.y	= 0.0;
	pl[0].pos.z	= 0.0;
	pl[0].m		= 100000.0;

	pl[1].pos.x	= 500.0;
	pl[1].pos.y	= -750.0;
	pl[1].pos.z	= -100.0;
	pl[1].vel.x	= -10.0;
	pl[1].vel.y	= 3.0;
	pl[1].vel.z	= 0.1;
	pl[1].m		= 0.001;

	pl[2].pos.x	= 200.0;
	pl[2].pos.y	= 250.0;
	pl[2].vel.x	= -6.0;
	pl[2].m		= 5000.0;

	for(int i=-5;i<=5;i++){
		planet p;
		p.m = 100.0;
		p.pos.x = 500.0 * i;
		for(int j=-5;j<=5;j++){
			if(i==0 && j==0) continue;
			p.pos.y = 500.0 * j;
			auto tmp = std::sqrt(i*i+j*j);
			p.vel.x = j / tmp;
			p.vel.y = -i/ tmp;
			p.vel = p.vel * 5.0;
			pl.push_back(p);
		}
	}

	for(int i=0;;i++){
		if(i%500==0) std::cout << "time=" << t << std::endl;
		if(i%500 == 0) save_prof(pl);
		time_step(pl, dt);
		t += dt;
		if(t > max_time) break;
	}

	return 0;
}

void calc_acc(std::vector<planet> &planet){
	// a = F / m
	// F = G * (m1+m2) / (dp^2)
	// ax= Fx/ m1
	// m = m1+m2
	// Fx= G * m / dx^2
	// Fy= G * m / dy^2
	// Fz= G * m / dz^2
	for(size_t i=0;i<planet.size();i++){
		auto& acc = planet[i].acc;
		acc.x = acc.y = acc.z = 0.0;
		for(size_t j=0;j<planet.size();j++){
			if(i == j) continue;
			const auto& mi = planet[i].m;
			const auto& mj = planet[j].m;
			if(mi==0.0 || mj==0.0) continue;
			auto d = planet[j].pos - planet[i].pos;
			auto r2= d.x*d.x + d.y*d.y + d.z*d.z;
			if(r2 == 0.0) continue;
			auto r = std::sqrt(r2);
			acc += d * (mj / (r*r2));
		}
	}
}

void time_step(std::vector<planet> &planet, const double &dt){
	calc_acc(planet);

	for(auto& p : planet){
		p.vel += p.acc * dt;
		p.pos += p.vel * dt;
	}
}

void save_prof(const std::vector<planet> &planet){
	static size_t count = 0;
	std::ostringstream fname;
	fname
		<< "out/"
		<< "output_"
		<< std::setfill('0')
		<< std::setw(5)
		<< count
		<< ".prof";

	std::ofstream file(fname.str());

	for(const auto& p : planet){
		file << p.pos.x << " "
			<< p.pos.y << " "
			<< p.pos.z << std::endl;
	}
	count++;
}
