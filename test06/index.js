const globalCache = require("./build/Release/globalCache");

function a(ss) {
    return ss;
}

let result = globalCache.set(a);

console.log(result);

globalCache.get(result);

// for (let i = 0; i < 100000; i++) {
//     console.log(globalCache.set(a));
// }
// console.log(globalCache.get());

setTimeout(() => {console.log(1)}, 10000);