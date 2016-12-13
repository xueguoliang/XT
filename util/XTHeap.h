/*
 * Copyright 2016 xueguoliang(xueguoliang@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef XTHEAP_H
#define XTHEAP_H

template <class T>
class XTHeap
{
public:
    XTHeap(int (*compare)(T*, T*), int step):
        datas(NULL),
        size(0),
        step(step),
        capacity(step),
        compare(compare)
    {
        datas = new T*[capacity];
    }

    ~XTHeap()
    {
        delete[] datas;
    }

    bool empty()
    {
        return size == 0;
    }

    T* at(int index)
    {
        if(index >= size) return NULL;
        return datas[index];
    }

    void add(T* data)
    {
        if(size == capacity)
        {
            int newcap = capacity + step;
            T** d = new T*[newcap];
            memcpy(d, datas, sizeof(T*)*capacity);
            delete [] datas;
            datas = d;
            capacity = newcap;
        }

        datas[size++] = data;
        addFix(size-1);
    }

    T* del(int index=0)
    {
        if(index >= this->size)
        {
            return NULL;
        }

        T* ret = datas[index];
        T* f = datas[--size];
        if(ret == f)
            return ret;

        int hole = delFix(index);
        datas[hole] = f;
        addFix(hole);
        return ret;
    }

private:
    int delFix(int i)
    {
        while (1) 
        {
            int l = i*2+1;
            int r = i*2+2;
            if(l >= size)
                return i;

            if(r >= size)
            {
                datas[i] = datas[l];
                return l;
            }

            int res = compare(datas[l], datas[r]);
            if(res <= 0)
            {
                datas[i] = datas[l];
                i = l;
            }
            else
            {
                datas[i] = datas[r];
                i = r;
            }
        }
    }

    void addFix(int i)
    {
        int p;
        while(i>0)
        {
            p = (i-1)/2;
            int res = compare(datas[p], datas[i]);
            if(res <= 0)
                break;

            T* tmp = datas[p];
            datas[p] = datas[i];
            datas[i] = tmp;
            i = p;
        }
    }

    T** datas;
    int size;
    int step;
    int capacity;
    int (*compare)(T*, T*);
};

#endif // XTHEAP_H
