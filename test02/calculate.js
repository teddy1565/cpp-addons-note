function calc() {
    let x = 100.32462344, y=200.333456533452;
    for (let i=0; i<100000000;i++) {
        x+=y;
    }
    const total = x;
    return total;
}

module.exports = { calc };