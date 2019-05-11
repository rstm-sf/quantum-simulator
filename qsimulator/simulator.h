// Copyright (C) 2018 - 2019 Rustam Sayfutdinov (rstm.sf@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
// BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef QSIMULATOR_SIMULATOR_H_
#define QSIMULATOR_SIMULATOR_H_

#include <cstdint>
#include <iostream>

#include "circuit.h"
#include "qreg.h"

namespace qsimulator {

class Simulator : public qengine::Circuit<double> {
public:
  Simulator() = delete;
  ~Simulator() = default;
  Simulator(const Simulator&) = delete;
  Simulator(Simulator&&) = delete;
  Simulator& operator=(const Simulator&) = delete;
  Simulator& operator=(Simulator&&) = delete;

  Simulator(uint64_t nreg, uint64_t dim)
    : qengine::Circuit<double>(nreg, dim) {}

  std::vector<qengine::CReg> get_result();
};

}

#endif //QSIMULATOR_SIMULATOR_H_
