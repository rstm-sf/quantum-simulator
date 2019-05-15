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

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <functional>
#include <numeric>
#include <vector>

#include "simulator.h"

int main() {
  const uint64_t n = 8;
  const uint64_t q = 1 << n;
  const auto epsilon = 0.2f;
  const auto dim = static_cast<const uint64_t>(
          std::llround(n / (epsilon * epsilon)));

  std::vector<uint64_t> k;
  k.reserve(dim);
  for (auto i = 0ULL; i < dim; ++i)
    k.push_back(i);

  const uint64_t word_a = 15;
  const uint64_t word_b = 15;

  const uint64_t nreg = 1;
  qsimulator::Simulator simulator(nreg, dim);

  const auto applyF0 = [&dim, &simulator] (uint64_t idx) -> void {
    for (uint64_t i = 1ULL; i < dim; ++i) {
      auto b = std::sqrt(static_cast<double>(dim - i) / dim);
      simulator.applyX(idx, i, std::sqrt(1.0 / dim), b);
    }
  };

  const auto applyF0conjugate = [&dim, &simulator] (uint64_t idx) -> void {
    for (uint64_t i = dim - 1; i > 0ULL; --i) {
      auto b = std::sqrt(static_cast<double>(dim - i) / dim);
      simulator.applyXconjugate(idx, i, std::sqrt(1.0 / dim), b);
    }
  };

  std::cout << "n   = " << n << "\n";
  std::cout << "q   = " << q << "\n";
  std::cout << "eps = " << epsilon << "\n";
  std::cout << "dim = " << simulator.dim() << "\n";
  std::cout << "a   = " << word_a << "\n";
  std::cout << "b   = " << word_b << "\n";
  for (const auto & k_i : k)
    std::cout << k_i << ", ";
  std::cout << std::endl;


  // Применение хеш-функции
  // Получаем состяние $\ket{\psi(a)}$
  applyF0(0);
  for (uint64_t i = 0; i < dim; ++i)
    simulator.applyZ(0, i, static_cast<double>(word_a * k[i]) / n);


  // Reverse-тест
  for (uint64_t i = 0; i < dim; ++i)
    simulator.applyZconjugate(
            0, dim - i - 1, static_cast<double>(word_b * k[dim - i - 1]) / n);
  applyF0conjugate(0);

  auto result = simulator.get_result();

  if (result[0] == 0LL) {
    std::cout << "\nTEST PASSED" << std::endl;
  } else {
    std::cout << "\nTEST FAIL" << std::endl;
  }

  return 0;
}