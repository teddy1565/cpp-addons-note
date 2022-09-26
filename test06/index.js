const globalCache = require("./build/Release/globalCache");
const http = require("http");


function helloworld(num, str) {
    console.log(num);
    console.log(str);
}
let heap = globalCache.set(helloworld);
console.log(heap);
globalCache.get(heap);


// console.log(heap);