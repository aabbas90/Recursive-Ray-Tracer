#include "fogtrace.h"
#include <core\color.h>
#include <rt\lights\light.h>
#include <rt\intersection.h>
#include <rt\coordmappers\coordmapper.h>
#include <rt\coordmappers\world.h>
#include <rt\world.h>
#include <rt\solids\solid.h>
#include <rt\materials\material.h>
#include <rt\lights\ambient.h>
#include <rt\fog\fog.h>

#define EPS 0.001
#define STEP 0.01
#define MAXDISTANCE 4

namespace rt {

	RGBColor RayFogTraceIntegrator::getRadiance(const Ray& ray, int depth) const {
		Intersection it = this->world->scene->intersect(ray, FLT_MAX);
		RGBColor color(0, 0, 0);
		if (it) {
			std::vector<Light *> vecLight = this->world->light;
			CoordMapper *cMapper = it.solid->texMapper;
			Point local;
			if (cMapper == nullptr) {
				WorldMapper wMapper(Float4::rep(1.0));
				local = wMapper.getCoords(it);
			}
			else {
				local = cMapper->getCoords(it);
			}
			for (unsigned int i = 0; i < vecLight.size(); i++) {
				Light* light = vecLight[i];
				Ray r;

				// Initially check for Ambient Light

				AmbientLight *aLight = dynamic_cast<AmbientLight *>(light);
				if (aLight) {
					LightHit lHit = aLight->getLightHit(it.hitPoint());
					r.d = lHit.direction;
					r.o = it.hitPoint() + EPS * r.d;
					Intersection itsec = this->world->scene->intersect(r, FLT_MAX);
					RGBColor irradiance = light->getIntensity(aLight->getLightHit(it.hitPoint())) * it.solid->material->getReflectance(local, it.normal(), (-1.0 * ray.d), r.d);
					if (this->world->fog != nullptr) {
						float attenuation = this->world->fog->getAttenuation(lHit.distance);
						irradiance = irradiance * attenuation;
					}
					color = color + irradiance;
				}
				else {
					// For othe Light Sources have to perform Ray-Marching in the presence for fog
					LightHit lHit = light->getLightHit(it.hitPoint());
					r.d = lHit.direction.normalize();
					r.o = it.hitPoint() + EPS * r.d;
					float distance = lHit.distance;
					if ((dot(-ray.d, it.normal()) > 0 && dot(r.d, it.normal()) > 0) || (dot(-ray.d, it.normal()) < 0 && dot(r.d, it.normal()) < 0)) {
						Intersection itsec = this->world->scene->intersect(r, FLT_MAX);
						if ((itsec.distance > distance) || (!itsec)) {
							RGBColor irradiance = rayMarching(light->getIntensity(lHit), it.distance, ray, false) * it.solid->material->getReflectance(local, it.normal(), (-1.0 * ray.d), -r.d);
							/*
							if (this->world->fog != nullptr) {
								float attenuation = this->world->fog->getAttenuation(distance);
								irradiance = irradiance * attenuation;
							}
							*/
							color = color + irradiance;
						}
					}
				}

			}
			color = color + it.solid->material->getEmission(local, it.normal(), (-1.0 * ray.d));


			if (this->world->fog != nullptr) {
				// ---------------For ambient Light uncomment here-------------------------
				/*
				float attenuation = this->world->fog->getAttenuation(it.distance);
				color = color * attenuation + (1 - attenuation) * this->world->fog->getIntensity(Point(0,0,0));
				*/
				// ---------------For othe light sourses uncomment here--------------------
				color = rayMarching(color, it.distance, ray, true);
			}
			return RGBColor(abs(color.r), abs(color.g), abs(color.b));
		}

		if (this->world->fog != nullptr) {
			// ---------------For ambient Light uncomment here-------------------------
			/*
			float attenuation = this->world->fog->getAttenuation(FLT_MAX);
			color = color * attenuation + (1 - attenuation) * this->world->fog->getIntensity(Point(0,0,0));
			return color;
			*/
			// ---------------For othe light sourses uncomment here--------------------

			color = rayMarching(color, MAXDISTANCE, ray, true);
			return color;

		}

	}


	RGBColor RayFogTraceIntegrator::rayMarching(RGBColor &intensity, float distance, const Ray &ray, bool lightFlag) const {
		RGBColor L = RGBColor::rep(0);
		RGBColor T = RGBColor::rep(1);
		float t = 0;
		float tStep = STEP;
		while (t < distance) {
			tStep = std::min(tStep, (distance - t));
			Point p = ray.o + (t + tStep / 2.0f) * ray.d;
			float b = world->fog->getAttenuation(tStep);
			RGBColor color = RGBColor::rep(0);
			if (lightFlag) {
				std::vector<Light *> vecLight = this->world->light;
				for (unsigned int i = 0; i < vecLight.size(); i++) {
					Light* light = vecLight[i];
					Ray r;
					LightHit lHit = light->getLightHit(p);
					r.d = lHit.direction.normalize();
					r.o = p + EPS * r.d;
					Intersection itsec = this->world->scene->intersect(r, FLT_MAX);
					if (itsec) continue;
					RGBColor irradiance = light->getIntensity(lHit);
					float attenuation = world->fog->getAttenuation(lHit.distance);
					irradiance = irradiance * attenuation;
					color = color + irradiance;
				}
			}
			L = L + T * (1 - b) * color * this->world->fog->getIntensity(p);
			T = T * b;
			t += STEP;
		}
		return intensity * T + L;
	}


}