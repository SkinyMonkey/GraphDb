#ifndef __NETWORK__
#define __NETWORK__

class Network : public INetwork
{
public:
	Network(){}
	~Network(){}

private:
	Network(const Network&);
	Network& operator=(const Network&);
};


#endif /* __NETWORK__ */
