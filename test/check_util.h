/*
 * check_util.h
 *
 * Copyright 2010-2012 Yahoo! Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  Created on: Jan 25, 2010
 *      Author: sears
 */

#ifndef CHECK_UTIL_H_
#define CHECK_UTIL_H_
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <vector>
#include <string>
bool mycmp(const std::string & k1,const std::string & k2)
{
    //for char* ending with \0
    return strcmp(k1.c_str(),k2.c_str()) < 0;

    //for int32_t
    //printf("%d\t%d\n",(*((int32_t*)k1)) ,(*((int32_t*)k2)));
    //return (*((int32_t*)k1)) <= (*((int32_t*)k2));
}

//must be given a sorted array
void removeduplicates(std::vector<std::string> *arr)
{

    for(int i=arr->size()-1; i>0; i--)
    {
        if(! (mycmp((*arr)[i], (*arr)[i-1]) || mycmp((*arr)[i-1], (*arr)[i])))
            arr->erase(arr->begin()+i);

    }

}
void scramble(std::vector<std::string> *arr) {
  for(unsigned int i = 0; i < arr->size(); i++) {
    unsigned int other = rand() % arr->size();
    if(other != i) {
      std::string s = (*arr)[i];
      (*arr)[i] = (*arr)[other];
      (*arr)[other] = s;
    }
  }
}

//must be given a sorted array
// XXX probably don't need two copies of this function.
void removeduplicates(std::vector<std::string> &arr)
{

    for(int i=arr.size()-1; i>0; i--)
    {
        if(! (mycmp(arr[i], arr[i-1]) || mycmp(arr[i-1], arr[i])))
            arr.erase(arr.begin()+i);

    }

}

void getnextdata(std::string &data, int avg_len)
{
    int str_len = (rand()%(avg_len*2)) + 3;

    data = std::string(str_len, rand()%10+48);
    /*
    char *rc = (char*)malloc(str_len);

    for(int i=0; i<str_len-1; i++)
        rc[i] = rand()%10+48;

    rc[str_len-1]='\0';
    data = std::string(rc);

    free(rc);
    */

}

void preprandstr(int count, std::vector<std::string> *arr, int avg_len=50, bool duplicates_allowed=false)
{

    for ( int j=0; j<count; j++)
    {
        int str_len = (rand()%(avg_len*2)) + 3;

        char *rc = (char*)malloc(str_len);

        for(int i=0; i<str_len-1; i++)
            rc[i] = rand()%10+48;

        rc[str_len-1]='\0';
        std::string str(rc);

        //make sure there is no duplicate key
        if(!duplicates_allowed)
        {
            bool dup = false;
            for(int i=0; i<j; i++)
                if(! (mycmp((*arr)[i], str) || mycmp(str, (*arr)[i])))
                {
                    dup=true;
                    break;
                }
            if(dup)
            {
                j--;
                continue;
            }
        }


        //printf("keylen-%d\t%d\t%s\n", str_len, str.length(),rc);
        free(rc);

        arr->push_back(str);

    }

}


void preprandstr(int count, std::vector<std::string> &arr, int avg_len=50, bool duplicates_allowed=false)
{

    for ( int j=0; j<count; j++)
    {
        int str_len = (rand()%(avg_len*2)) + 3;

        char *rc = (char*)malloc(str_len);

        for(int i=0; i<str_len-1; i++)
            rc[i] = rand()%10+48;

        rc[str_len-1]='\0';
        std::string str(rc);

        //make sure there is no duplicate key
        if(!duplicates_allowed)
        {
            bool dup = false;
            for(int i=0; i<j; i++)
                if(! (mycmp(arr[i], str) || mycmp(str, arr[i])))
                {
                    dup=true;
                    break;
                }
            if(dup)
            {
                j--;
                continue;
            }
        }


        //printf("keylen-%d\t%d\t%s\n", str_len, str.length(),rc);
        free(rc);

        arr.push_back(str);

    }

}

static inline double tv_to_double(struct timeval tv)
{
  return static_cast<double>(tv.tv_sec) +
      (static_cast<double>(tv.tv_usec) / 1000000.0);
}

#endif /* CHECK_UTIL_H_ */
