const findPrime = require("./findPrime");
const findPrimeNateive = require("./build/Release/findprimes");
const calc = require("./build/Release/calculate");
const calcJS = require("./calculate");

const input = 200000;


console.time("c++");
calc.calc();
console.timeEnd("c++");
console.time("calcJS");
calcJS.calc();
console.timeEnd("calcJS");



console.time("Native");
findPrimeNateive(input);
console.timeEnd("Native");

console.time("js");
findPrime(input);
console.timeEnd("js");