#include <map>
#include <string>

// FIXME : have a map with multiple key type

typedef	struct	data
{
	enum
	{
		INT,
		STRING
	}			type;
	union
	{
		int			i_val;
		std::string	s_val;
	}				u;


}					s_data

int		main(void)
{
	std::map<IData, int>	test;
	Data<std::string>		t("un");

	test[t] = 1;
}
