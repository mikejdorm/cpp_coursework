//
//  my_async.h
//  CSPP51045_HW18
//
//  Created by Michael Dorman on 5/19/12.
//  Copyright (c) 2012 DePaul University. All rights reserved.
//

#ifndef CSPP51045_HW18_my_async_h
#define CSPP51045_HW18_my_async_h
#include <future> 
#include <type_traits>
#include <memory>

namespace cspp51045{

    template<class Func, class... Args>
    std::future<typename std::result_of<Func()>::type>  my_async(Func func, Args... args){
        typedef typename std::result_of<Func()>::type func_type; 
        std::packaged_task<func_type()> my_task(func(args...)); 
        std::future<func_type> answer = my_task.get_future();
        std::thread t(std::move(my_task));
        t.detach();
        return answer;
    }
    
    template<class Func>
    std::future<typename std::result_of<Func()>::type>  my_async(Func func){
        typedef typename std::result_of<Func()>::type func_type;       
        std::packaged_task<func_type()> my_task(func); 
        std::future<func_type> answer = my_task.get_future();
        std::thread t(std::move(my_task));
        t.detach();
        return answer;
    }
  
}


#endif
