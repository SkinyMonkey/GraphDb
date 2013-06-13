#ifndef __SEARCHENGINE__
#define __SEARCHENGINE__

class SearchEngine : public ISearchEngine
{
public:
	SearchEngine(){}
	~SearchEngine(){}

private:
	SearchEngine(const SearchEngine&);
	SearchEngine& operator=(const SearchEngine&);
	/* data */
};


#endif /* __SEARCHENGINE__ */
