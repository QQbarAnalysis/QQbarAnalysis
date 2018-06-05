
#include <iostream>
#include <vector>
#ifndef _TreeEntry_hh
#define _TreeEntry_hh
namespace QQbarProcessor 
{
	template <class T> class TreeEntry 
	{
		public:
		//
		//	Constants
		//
	
		//
		//	Constructors
		//
			TreeEntry (std::string name, std::type);
			virtual ~TreeEntry () {};
			std::string GetName();
			const * T GetValue() const;
			SetValue(T  value);


		//
		//	Methods
		//
		
		private:
		//
		//	Data
		//
			T myValue;
			std::string myName;
			std::string myType;
		//
		//	Private methods
		//
	};
} /* QQbarProcessor */
#endif
