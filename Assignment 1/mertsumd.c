#include <stdio.h>

#define MAXEXP 8

int main()
{
    /*loop/print limit(s)*/
    int exp, low, high;
    exp = MAXEXP;
    low = 1;
    high = 19;

    /*square-free calculations*/
    int n, temp, fact_count, factor;
    int is_square_free; /*bool*/
    n = 1;

    /*mertens function and zero points of it*/
    int mertens_sum, zp;
    mertens_sum = 0;
    zp = 0;

    /*perfect/deficient/abundant numbers calculations*/
    int prime_prod, term;
    int deficient, abundant;
    deficient = 0;
    abundant = 0;

    /*
        exp shows us how much more
        high and low need to be multiplied

        after exp reaches 0 we have exceeded 10^MAXEXP + 9
        so we don't need to check for more numbers
    */
    while (exp > 0)
    {
        /*
            eliminate multiples of 4 and 9 because
            2^2 or 3^2 divide them and therefore are not
            square-free numbers
        */
        if (n % 4 != 0 && n % 9 != 0)
        {
            temp = n;
            fact_count = 0;
            is_square_free = 1;

            /*
                check for 2 and 3 only once,
                because the number is not multiple of 4 or 9
            */
            if (temp % 2 == 0)
            {
                temp /= 2;
                fact_count++;
            }
            if (temp % 3 == 0)
            {
                temp /= 3;
                fact_count++;
            }

            factor = 5;
            while (factor * factor <= temp)
            {
                if (temp % factor == 0)
                {
                    temp /= factor;

                    if (temp % factor == 0)
                    {
                        /*
                            if the factor divides the number
                            at least two times, the number
                            is not square-free
                        */
                        is_square_free = 0;
                        break;
                    }

                    fact_count++;
                }

                /*
                    check two factors every pair of six numbers
                    because we have eliminated multiples of 2 and 3
                */
                if (factor % 6 == 5)
                {
                    factor += 2;
                }
                else
                {
                    factor += 4;
                }
            }

            if (is_square_free == 1)
            {
                if (temp != 1) /*incase there's one more divisor left*/
                {
                    fact_count++;
                }
                if (fact_count % 2 == 0)
                {
                    mertens_sum++;
                }
                else
                {
                    mertens_sum--;
                }
            }
        }

        if (mertens_sum == 0)
        {
            zp++;
        }

        if (n >= low && n <= high)
        {
            printf("M(%d) = %d\n", n, mertens_sum);

            if (n == high) /*next pair of limits*/
            {

                /*
                    every time n exceeds high, the exponent
                    of 10 in high and low increaces by 1
                */
                low += 9;
                low *= 10;
                low -= 9;

                high -= 9;
                high *= 10;
                high += 9;

                /*decreases the times high and low need to be multiplied*/
                exp--;

                if (exp > 0) /*check if we finished so we don't print dots at the end*/
                {
                    printf("..........\n");
                }
            }
        }

        n++;
    }

    printf("\nFound %d zero points of the Mertens function\n\n", zp);

    printf("Checking numbers in the range [%d,%d]\n\n", 2, (1000 * zp));
    for (n = 2; n <= 1000 * zp; n++)
    {
        prime_prod = 1;
        temp = n;
        factor = 2;

        /*
            The sum D of the divisors of a number is equal to
            the product, of the sum, of the powers, of its prime factors.
            The powers are in the range [0, k] where k is the biggest power in which
            the factor can divide the number

            D == (d1 + d2 + d3 + d3 + ... + number)
            or
            D == (1 + p1 + p1^2 + ... + p1^k)*(1 + p2 + p2^2 + ... +p2^l)*...

            therefore the sum of the proper divisors of a number is D - number
        */

        while (factor * factor <= temp)
        {
            term = 1;
            while (temp % factor == 0)
            {
                /*
                    Do (term = factor * term + 1) to
                    add one more power of the prime factor

                    term = 1 + factor + factor^2 + ... + factor^k =>
                    term = 1 + factor + factor^2 + ... + factor^(k+1)
                */
                term = 1 + factor * term;
                temp /= factor;
            }
            prime_prod *= term;

            if (factor == 2)
            {
                factor = 3;
            }
            else if (factor == 3)
            {
                factor = 5;
            }
            else if (factor % 6 == 5)
            {
                factor += 2;
            }
            else
            {
                factor += 4;
            }
        }

        if (temp != 1) /*incase there's one more divisor left*/
        {
            prime_prod *= (1 + temp);
        }

        prime_prod -= n; /*sum of divisors becomes proper sum of divisors*/
        if (prime_prod == n)
        {
            printf("Found perfect number: %d\n", n);
        }
        else if (prime_prod < n)
        {
            deficient++;
        }
        else
        {
            abundant++;
        }
    }

    printf("\nFound %d deficient numbers\n", deficient);
    printf("Found %d abundant numbers\n", abundant);
}
