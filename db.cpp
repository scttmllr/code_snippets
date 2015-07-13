#include <iostream>
#include <memory>
#include <list>
#include <string>
#include <cassert>

namespace db {
    
template <typename Type>
void dbDataDeleteFunc(void* p)
{
    delete static_cast<Type*>(p);
}

class dbEntry
{
public:
    dbEntry() = delete;
    dbEntry(const dbEntry &dbe) = delete;
    
    dbEntry(const std::string label, std::unique_ptr<void, void(*)(void*)>& data)
    : data(std::move(data)), label(label) {};
    
    ~dbEntry(){std::cout<<"\n  Deleting dbEntry for " << label << std::endl;};
    
    void operator=(const dbEntry &dbe) = delete;
    
    std::unique_ptr<void, void(*)(void*)> data;
    std::string label;
};

class dbmgr
{
private:
    
    std::list<std::unique_ptr<dbEntry> > mEntries;
    
    std::list<std::unique_ptr<dbEntry> >::iterator
    FindEntry(const std::string &label)
    {
        for (auto i=mEntries.begin(); i!=mEntries.end(); ++i)
        {
            if((*i)->label == label)
                return i;
        }
        
        return mEntries.end();
    }
    
public:
    
    dbmgr(){};
    ~dbmgr(){};
    
    template <typename Type>
    void PutData(const std::string &label,
                 std::unique_ptr<Type>& data)
    {
        auto entry=FindEntry(label);
        
        std::unique_ptr<void, void(*)(void*)>
        dataWithDeleter(data.release(), dbDataDeleteFunc<Type>);
        
        if(entry == mEntries.end())
        {
            mEntries.push_back(std::unique_ptr<dbEntry>(new dbEntry(label, dataWithDeleter)));
        }
        else
        {
            (*entry)->data.swap(dataWithDeleter);
        }
    }
    
    
    template <typename Type>
    const Type* GetData(const std::string &label)
    {
        auto entry = FindEntry(label);
        assert(entry!=mEntries.end());
        return static_cast<Type*>((*entry)->data.get());
    }
};
    
}//db namespace


int main(int argc, const char * argv[]) {
    
    db::dbmgr dataHandler;

    {
    std::unique_ptr<int> iArray(new int[7]);
    std::unique_ptr<double> dArray(new double(3.14159));
    std::unique_ptr<char> cArray(new char[13]);
    
    dataHandler.PutData("int", iArray);
    dataHandler.PutData("double", dArray);
    dataHandler.PutData("char", cArray);

    std::cout<<"\nUnique pointers in main going out of scope..."<<std::endl;
    }

    const double *dData = dataHandler.GetData<double>("double");
    const int *iData = dataHandler.GetData<int>("int");
    const char *cData = dataHandler.GetData<char>("char");
    
    std::cout<<"\nSuccessfully got data from dbmgr data.\nExiting main."<<std::endl;
    
    return 0;
}