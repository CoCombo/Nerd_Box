#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cmath>
#define USERS 500
#define CONTEXTS 7
#define MOVIES 1683
#define TOPK 5
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;

struct User
{
    string context;
    string social;

    int userID;
    int countContext;
    int age;
    char gender;
    User() : social(10, '_') {}
};

bool include(string src, string des)
{
    for(int i = 0; i < CONTEXTS; i++)
        if( src[i] == '1' && des[i] != '1' )
            return false;
    return true;
}

int ones(string str)
{
    int s = 0;
    for(auto i : str)
        if(i == '1')
            s++;
    return s;
}

bool onlyOne(string str)
{
    int count = 0;
    for(auto i : str)
        if(i == '1')
            count++;
    return count == 1;
}

int main()
{
    vector<User> UCB(USERS);
    vector<string> GCB, UG;
    vector<string> userInfo;
    float movieprediction[USERS][MOVIES];
    char info[40];
    string groupPattern;

    ifstream socialInfo("./user"), prediction("./prediction");
    ofstream outUCB, outGCB, outUG;

    outUCB.open("./UCB.txt");
    outGCB.open("./GCB.txt");
    outUG.open("./UG.txt");

    int groupCount = 0;

    /*generate random context*/
    /*for(int i = 0; i < USERS && !socialInfo.eof(); i++)
    {
        socialInfo.getline(info, 40);
        for(int j = 0; j < CONTEXTS; j++)
            UCB[i].context.push_back(std::rand() % 2 ? '1' : '_');
        UCB[i].countContext = ones(UCB[i].context);
        UCB[i].userID = i;

        for(int j = 0; j < 30; j++)
          if(info[j] == 'M' || info[j] == 'F')
          {
                int age;
                UCB[i].social[9] = info[j];
                age = info[j-2] - 48;
                if(info[j-3] != '|')
                    age += (info[j-3] - 48) * 10;
                UCB[i].social[age / 10] = '1';
          }
    }*/
    /*for(auto i : UCB)
    {
        cout << i.social << " " << i.context <<endl;
    }*/
    //sort
    vector<User> copyUCB(UCB);
    std::sort(copyUCB.begin(), copyUCB.end(), [](User a, User b) { return a.countContext < b.countContext; });

    /*print UCB*/
    /*for(auto i : UCB)
        cout << "U"
             << i.userID
             << ": "
             << i.context
             //<< " " << i.age << i.gender
             << endl;
    cout << endl;
    /*print UCB to file*/
    for(auto i : UCB)
        outUCB << i.context << " "<< i.social << endl;
    /*
    for(int i = 0; i < USERS; i++)
    {
        vector<string> copyUCB(UCB);
        for(auto &j : copyUCB)
        {
            for(int k = 0; k < CONTEXTS; k++)
            {
                if(UCB[i][k] != 'x' && j[k] != 'x')
                    j[k] = '0';
                if(j[k] == '1')
                    j[k] = 'x';
            }
        }
        groupPattern = copyUCB[i];
        if( !GCB.empty() )
        {
            //cout << "have groupPattern." << endl;
            for(auto i : GCB)
                if( include(i, groupPattern) )
                {
                    //cout << "include: " << i << endl;
                    for(int j = 0; j < CONTEXTS; j++)
                        if( i[j] == '0' )
                            groupPattern[j] = 'x';
                }
            if(groupPattern != "xxxxxxx" && !zeros(groupPattern))
                GCB.push_back(groupPattern);
        }
        else
            GCB.push_back(groupPattern);
        /*for(auto &j : copyUCB)
            cout << j << endl;
        cout << endl;
        cout << "GCB:" << endl;*/
        /*for(auto i : GCB)
            cout << i << endl;*/
    //}

    /*group detection*/
    for(int i = 0; i < USERS; i++)
    {
        groupPattern = copyUCB[i].context;
        if( !GCB.empty() )
        {
            for(auto j : GCB)
            {
                if( include(j, groupPattern) )
                {
                    for(int k = 0; k < CONTEXTS; k++)
                        if(j[k] == '1')
                            groupPattern[k] = '_';
                }
            }
            if(groupPattern != "_______" && !onlyOne(groupPattern))
                GCB.push_back(groupPattern);
        }
        else
            GCB.push_back(groupPattern);
    }
    groupCount = GCB.size();

    /*print GCB*/
    //cout << "GCB: " << endl;
    /*for(int i = 0; i < groupCount; i++)
        cout << "G"
             << i
             << ": "
             << GCB[i]
             <<endl;
    cout << "Group Count: " << groupCount << endl;
    /*output to GCB file*/
    /*for(int i = 0; i < groupCount; i++)
        outGCB << GCB[i] <<endl;
    outGCB << "Group Count: " << groupCount << endl;

    /*UG*/
    for(int i = 0; i < USERS; i++)
    {
        string UGpattern(groupCount, '_');
        for(int j = 0; j < groupCount; j++)
        {
            if( include(GCB[j], UCB[i].context) )
                UGpattern[j] = '1';
        }
        UG.push_back(UGpattern);
    }

    /*print UG*/
    /*cout << "UG: " << endl;
    for(int i = 0; i < USERS; i++)
        cout << "U" << i << ": "
             << UG[i] <<endl;
    /*output to UG file*/
    /*for(int i = 0; i < USERS; i++)
        outUG << UG[i] <<endl;*/

    /*social group*/
    int SGCount = 0;
    vector< vector<int> > SG;
    for(int j = 0; j < CONTEXTS; j++)
    {
        /*catch group user ID*/
        vector<int> groupID;
        for(int i = 0; i < USERS; i++)
        {
            if(UG[i][j] == '1')
            {
                groupID.push_back(i);
            }
        }
        /*for(auto i : groupID)
            cout << i << " ";
        cout << endl;*/
        int groupsize = groupID.size();
        for(int i = 0; i < groupsize; i++)
        {
            vector<int> socialgroupID;
            string tmpsocial;
            if(groupID[i] != -1)
            {
                socialgroupID.push_back(groupID[i]);
                tmpsocial = UCB[groupID[i]].social;
                groupID[i] = -1;
            }
            for(int k = i + 1; k < groupsize; k++)
            {
                if(groupID[k] != -1 && tmpsocial == UCB[groupID[k]].social)
                {
                    socialgroupID.push_back(UCB[groupID[k]].userID);
                    groupID[k] = -1;
                }
            }
            if(!socialgroupID.empty())
            {
                SG.push_back(socialgroupID);
                SGCount++;
            }
        }
    }
    //cout << groupCount << endl;
    cout << "UG:" << groupCount <<endl;
    cout << "SG:" << SGCount << endl;
    for(auto i : SG)
    {
        if(i.size() == 1)
            cout << i[0] << " ";
    }

    /*prediction*/
    for(int i = 0; i < USERS; i++)
        for(int j = 0; j < MOVIES; j++)
            movieprediction[i][j] = -1;

    while( !prediction.eof() )
    {
        char movieinfo[20];
        string user, movie, rate;
        prediction.getline(movieinfo, 20);
        int i = 0;
        for(; movieinfo[i] != ' '; i++)
        {
            user.push_back(movieinfo[i]);
        }
        int usernum = std::atoi(user.c_str());
        //cout << usernum << " ";
        /*prevent read last line*/
        if(usernum == 0)
            break;
        i++;
        for(; movieinfo[i] != ' '; i++)
        {
            movie.push_back(movieinfo[i]);
        }
        int movienum = std::atoi(movie.c_str());
        i++;
        for(; movieinfo[i] != '.'; i++);
        rate.push_back(movieinfo[i-1]);
        rate.push_back(movieinfo[i+1]);
        float ratenum = (static_cast<float>(std::atoi(rate.c_str()))) / 10;
        movieprediction[usernum-1][movienum] = ratenum;
        //cout << usernum << " " << movienum << " " << ratenum << endl;
        //cout << movieprediction[-3][movienum] <<endl;
    }
    /*for(int i = 3; i < 4; i++)
    {
        for(int j = 1; j < MOVIES; j++)
            if(movieprediction[i][j] != -1)
                cout << movieprediction[i][j] << " ";
        cout << endl;
    }*/
    vector< vector<int> > contextgroup;
    for(int i = 0; i < groupCount; i++)
    {
        vector<int> group;
        for(int j = 0; j < USERS; j++)
        {
            if(UG[j][i] == '1')
                group.push_back(j);
        }
        contextgroup.push_back(group);
    }
    //cout << contextgroup.size();
    float groupAverageRate[groupCount][MOVIES];
    for(int i = 0; i < groupCount; i++)
        for(int j = 0; j < MOVIES; j++)
            groupAverageRate[i][j] = 0.0;
    for(int i = 0; i < groupCount; i++)
    {
        for(int k = 1; k < MOVIES; k++)
        {
            int count = 0;
            for(int j = 0; j < contextgroup[i].size(); j++)
            {
                if(movieprediction[contextgroup[i][j]][k] > 0.0)
                {
                    groupAverageRate[i][k] += movieprediction[contextgroup[i][j]][k];
                    count++;
                }
            }
            if(count)
            {
                //cout << groupAverageRate[i][k] << " " << count << " " << endl;
                groupAverageRate[i][k] /= count;
            }
        }
    }

    float socialAverageRate[SGCount][MOVIES];
    for(int i = 0; i < SGCount; i++)
        for(int j = 0; j < MOVIES; j++)
            socialAverageRate[i][j] = 0.0;
    for(int i = 0; i < SGCount; i++)
    {
        for(int k = 1; k < MOVIES; k++)
        {
            int count = 0;
            for(int j = 0; j < SG[i].size(); j++)
            {
                if(movieprediction[SG[i][j]][k] > 0.0)
                {
                    socialAverageRate[i][k] += movieprediction[SG[i][j]][k];
                    count++;
                }
            }
            if(count)
            {
                //cout << socialAverageRate[i][k] << " " << count << " " << endl;
                socialAverageRate[i][k] /= count;
            }
        }
    }
    /*for(int i = 0; i < groupCount; i++)
    {
        for(int j = 1; j < MOVIES; j++)
            cout << groupAverageRate[i][j] << " ";
        cout << endl;
    }*/
    for(int i = 0; i < groupCount; i++)
    {
        vector<float> tmp;
        for(int j = 1; j < MOVIES; j++)
            tmp.push_back(groupAverageRate[i][j]);
        std::sort(tmp.begin(), tmp.end(), [](float a, float b) { return a > b; });
        for(int j = 1; j < MOVIES; j++)
            groupAverageRate[i][j] = tmp[j-1];
    }
    for(int i = 0; i < SGCount; i++)
    {
        vector<float> tmp;
        for(int j = 1; j < MOVIES; j++)
            tmp.push_back(socialAverageRate[i][j]);
        std::sort(tmp.begin(), tmp.end(), [](float a, float b) { return a > b; });
        for(int j = 1; j < MOVIES; j++)
            socialAverageRate[i][j] = tmp[j-1];
    }
    /*for(int i = 0; i < groupCount; i++)
    {
        for(int j = 1; j < MOVIES; j++)
            cout << groupAverageRate[i][j] << " ";
        cout << endl;
    }*/
    /*for(int i = 1; i < 2; i++)
    {
        for(int j = 1; j < MOVIES; j++)
            cout << socialAverageRate[i][j] << " ";
        cout << endl;
    }*/
    /*for(int i = 0; i < USERS; i++)
    {
        vector<float> tmp;
        for(int j = 1; j < MOVIES; j++)
            tmp.push_back(movieprediction[i][j]);
        std::sort(tmp.begin(), tmp.end(), [](float a, float b) { return a > b; });
        for(int j = 1; j < MOVIES; j++)
            movieprediction[i][j] = tmp[j-1];
    }*/
    /*for(int i = 0; i < USERS; i++)
    {
        for(int j = 1; j < MOVIES; j++)
            if(movieprediction[i][j] != -1)
                cout << movieprediction[i][j] << " ";
        cout << endl;
    }*/
    float DCG = socialAverageRate[1][1];
    for(int i = 2; i <= 20; i++)
    {
        //cout << socialAverageRate[1][i-1] << endl;
        DCG += ((socialAverageRate[1][i]) / (std::log(float(i)) / std::log(2.0)));
    }
    float IDCG = 5.0;
    for( int i = 2; i <= 20; i++)
    {
        //cout << IDCG << endl;
        IDCG += (5.0) / (std::log(float(i)) / std::log(2.0));
    }
    cout << DCG / IDCG;
    outUCB.close();
    outUG.close();
    return 0;
}
