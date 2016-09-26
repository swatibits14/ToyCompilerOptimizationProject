#include<stdlib.h>
#include <stdio.h>
#include"set.h"

typedef Symbol;

void extractRules(FILE* fp)
{
	char line[MAX_LINE];
	while(fscanf(fp,"%s",line)!=EOF)
	{
		makeRule(line);
	}

	
}

/*first(Set firstSet,List* fromHere)
{

	List* itr;
	itr=fromHere;
	while(itr!=NULL)
	{
		if(isTerminal(itr->element))
		{
			addToSet(firstSet,itr->element);
			break;
		}
		if(containsE(itr->element))
		{
			addToSet
		}

	}

}*/

Set first(Symbol NTs[],List* allRules)
{

	List* itr;
	itr=fromHere;
	while(itr!=NULL)
	{
		if(isTerminal(itr->element))
		{
			addToSet(firstSet,itr->element);
			break;
		}
		if(containsE(itr->element))
		{
			addToSet
		}

	}
	//////////////////////////////////////////////
		Set ans;

        Symbol firstNT = NTs[0];

            if (!firstNT.isNT)
            {
                addToSet(ans,NTs[0]);
                return ans;
            }

            if(NTs.Count==1)
            {
                List<Rule> startRules = findAllStartRules(NTs[0], allRules);
                foreach (Rule r in startRules)
                {
                    ans.UnionWith(First(r.rhs, allRules));
                }
                return ans;
            }


            List<Symbol> singletonList = new List<Symbol>(); singletonList.Add(firstNT);
            
            HashSet<Symbol> firstOfFirstNT = First(singletonList, allRules);

            if(!firstOfFirstNT.Contains(new Symbol("e", false)))
            {
                return firstOfFirstNT;
            }
            else
            {
                firstOfFirstNT.Remove(new Symbol("e", false));
                List<Symbol> NTs_Copy = new List<Symbol>(NTs);
                NTs_Copy.Remove(firstNT);
                firstOfFirstNT.UnionWith(First(NTs_Copy, allRules));
                return firstOfFirstNT;
            }

}