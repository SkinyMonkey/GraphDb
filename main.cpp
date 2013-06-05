#include <iostream>
#include "Node.hpp"
#include "Attributes.hpp"

int			main(void)
{
	Node		test;
	Node		test2;
	Attributes	A;

	A.add_attribute("contamination", "true");
	test.add_attribute("contamination"
					  ,A.get_attribute("contamination", "true"));
	std::cout << test["contamination"] << std::endl;
	A.dump_attributes_edges("contamination", "true");

	test.add_connexion(&test2);
	std::cout << "----- dump -----" << std::endl;
	std::cout << "original : " << test2.id() << std::endl;
	test.dump_edges();
	test2.dump_edges();
	test.remove_connexion(&test2);
	test.dump_edges();
}
