
#include "Triangle.hpp"

#include <glm/gtc/epsilon.hpp>


Triangle::Triangle(const glm::vec3 & v1, const glm::vec3 & v2, const glm::vec3 & v3)
{
	a = v1;
	b = v2;
	c = v3;

	normal = glm::normalize(glm::cross(b - a, c - a));
}

bool Triangle::Intersect(Ray const & ray, RayHitResults * const hit) const
{
	static const float epsilon = 0.0001f;

	const glm::vec3 p = ray.origin;
	const glm::vec3 d = ray.direction;

	glm::vec3 e1, e2, h, s, q;

	glm::vec3 v0 = a, v1 = b, v2 = c;

	float a,f,u,v;
	e1 = v1 - v0;
	e2 = v2 - v0;

	h = glm::cross(d, e2);
	a = glm::dot(e1,h);

	if (glm::epsilonEqual(a, 0.f, epsilon))
		return false;

	f = 1 / a;
	s = p - v0;
	u = f * glm::dot(s,h);

	if ((u < 0.f || u > 1.f) && ! glm::epsilonEqual(u, 0.f, epsilon) && ! glm::epsilonEqual(u, 1.f, epsilon))
		return false;

	q = glm::cross(s, e1);
	v = f * glm::dot(d,q);

	if ((v < 0.f || u + v > 1.f) && ! glm::epsilonEqual(v, 0.f, epsilon) && ! glm::epsilonEqual(u + v, 1.f, epsilon))
		return false;

	const float t = f * glm::dot(e2,q);

	if (t >= 0.f || glm::epsilonEqual(t, 0.f, epsilon))
	{
		hit->t = t;
		hit->point = ray.origin + ray.direction * t;
		hit->normal = normal;
		hit->object = this;

		return true;
	}
	else
	{
		return false;
	}
}

std::string Triangle::GetObjectType() const
{
	return "Triangle";
}
