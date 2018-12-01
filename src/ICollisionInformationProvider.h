#ifndef ICOLLISIONINFORMATIONPROVIDER_H
#define ICOLLISIONINFORMATIONPROVIDER_H

class ICollisionInformationProvider
{
	public:
		virtual bool isCollidable(const unsigned int tx, const unsigned int ty) const = 0;
};

#endif // ICOLLISIONINFORMATIONPROVIDER_H
