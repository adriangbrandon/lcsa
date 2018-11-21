/***
BSD 2-Clause License

Copyright (c) 2018, Adrián
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/


//
// Created by Adrián on 19/11/2018.
//
#include <chrono>
#include <fstream>
#include <iostream>
#include <sdsl/csa_bitcompressed.hpp>
#include <lcsa.hpp>

int main(int argc, char **argv) {


    //Paso 1

    if(argc != 2){
        std::cout << argv[0] << " <input>" << std::endl;
        exit(0);
    }
    using timer = std::chrono::high_resolution_clock;
    std::ifstream ifs(argv[1]);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );


    std::cout << "Reading: " << content.size() << " bytes" << std::endl;

    sdsl::csa_bitcompressed<> csa;
    sdsl::construct_im(csa, content, 1);

    std::cout << "Csa" << std::endl;
    lcsa::lcsa m_lcsa(csa, 64);
    std::cout << "LCSA" << std::endl;
    /*for(uint64_t i = 0; i < m_lcsa.size(); i++){
       if(m_lcsa[i] != csa[i]){
           std::cout << "Error salc[" << i << "] " << m_lcsa[i] << " != csa[" << i << "] " << csa[i]<< std::endl;
           exit(1);
       };

    }*/

    auto start = timer::now();
    for(uint64_t i = 0; i < 1000; i++){
        m_lcsa[i];
    }
    auto stop = timer::now();
    auto time_lcsa = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()/(double)1000;

    start = timer::now();
    for(uint64_t i = 0; i < 1000; i++){
        csa[i];
    }
    stop = timer::now();
    auto time_sa = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()/(double)1000;


    std::cout << "Bytes SA " << sdsl::size_in_bytes(csa) << std::endl;
    std::cout << "Bytes LCSA " << m_lcsa.size_in_bytes() << std::endl;
    std::cout << "Time per element LCSA: " << time_lcsa / content.size() << std::endl;
    std::cout << "Time per element SA: " << time_sa / content.size() << std::endl;

}

