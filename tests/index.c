#include <stdio.h>
#include <strings.h>

static const char * fable = "\
A PEDDLER drove his Ass to the seashore to buy salt.  His road \
home lay across a stream into which his Ass, making a false step, \
fell by accident and rose up again with his load considerably \
lighter, as the water melted the sack.  The Peddler retraced his \
steps and refilled his panniers with a larger quantity of salt \
than before.  When he came again to the stream, the Ass fell down \
on purpose in the same spot, and, regaining his feet with the \
weight of his load much diminished, brayed triumphantly as if he \
had obtained what he desired.  The Peddler saw through his trick \
and drove him for the third time to the coast, where he bought a \
cargo of sponges instead of salt.  The Ass, again playing the \
fool, fell down on purpose when he reached the stream, but the \
sponges became swollen with water, greatly increasing his load. \
And thus his trick recoiled on him, for he now carried on his \
back a double burden.";

int main(int argc, char ** argv) {
    char * ret = index(fable, 'e');
    fprintf(stdout, "%s\n", ret);

    ret = rindex(fable, 'e');
    fprintf(stdout, "%s\n", ret);

    ret = index(fable, 'R');
    fprintf(stdout, "%s\n", ret);

    ret = rindex(fable, 'R');
    fprintf(stdout, "%s\n", ret);

    (void)argc;
    (void)argv;
    return 0;
}

