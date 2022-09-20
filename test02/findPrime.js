function isPrime(num) {
    if (num <= 1) {
        return 0;
    }

    for (let i = 2; i <= num/2; i++) {
        if (num % i == 0) {
            return 0;
        }
    }

    return 1;
}

function find_prime(upper_limit) {
    let largest_prime = 2;

    for (let i = 2; i <= upper_limit; i++) {
        if (isPrime(i)) {
            largest_prime = i;
        }
    }

    return largest_prime;
}

module.exports =  find_prime ;