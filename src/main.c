#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <estia-image.h>
#include <getopt.h>

#include "features.h"
#include "utils.h"
#include "argsparse.h"

int main(int argc, char **argv) {
  /*To use debug mode: 
   - add --debug: freud.exe --debug -f images/input/image.jpeg
   or 
   - Simply run your compiled project with start button on the blue menu bar at the bottom of the VS Code window.
   */

  /*DO NOT EDIT THIS PART*/
  Config configuration ;
  parse_arguments( argc, argv, &configuration ) ;
  check_debug_mode(configuration);
  check_file();
  /* END */

  /* Use "if ( strncmp( command, <commandname>, 9 ) == 0 )" to check if your <commandname> is called by program.*/
  /* Example with helloworld command
   * If helloworld is a called command: freud.exe -f images/input/image.jpeg -c helloworld 
   */
  if ( strncmp( configuration.command, "helloworld", 10 ) == 0 ) {
    /* helloworld() function is defined in feature.h and implemented in feature.c */
    helloWorld();
  } else if ( strcmp( configuration.command, "dimension") == 0 ) {
    dimension(configuration.filenames[0]);
  } else if ( strncmp( configuration.command, "first_pixel", 11 ) == 0 ) {
    first_pixel(configuration.filenames[0]);
  } else if ( strcmp(configuration.command, "second_line") == 0 ) {
    second_line(configuration.filenames[0]);
  } else if ( strncmp( configuration.command, "tenth_pixel", 10 ) == 0 ) {
    tenth_pixel(configuration.filenames[0]);
  } else if ( strcmp(configuration.command, "max_pixel") == 0){
    max_pixel(configuration.filenames[0]);
  }
  else if (strcmp(configuration.command, "print_pixel") == 0) {
    int x = atoi(argv[argc - 2]);  
    int y = atoi(argv[argc - 1]);  
    print_pixel(configuration.filenames[0], x, y);
  } else if ( strncmp( configuration.command, "min_pixel", 9) == 0 ) {
    min_pixel(configuration.filenames[0]);
  } else if (strcmp(configuration.command, "color_red") == 0) {
    color_red(configuration.filenames[0]);
  } else if (strcmp(configuration.command, "color_green") == 0) {
    color_green(configuration.filenames[0]);
  } else if (strcmp(configuration.command, "color_blue") == 0) {
    color_blue(configuration.filenames[0]);
  } else if (strcmp(configuration.command, "color_gray") == 0) {
    color_gray(configuration.filenames[0]);
  } else if (strcmp(configuration.command, "color_gray_luminance") == 0) {
    color_gray_luminance(configuration.filenames[0]);
  }else if (strcmp(configuration.command, "color_desaturate") == 0) {
    color_desaturate(configuration.filenames[0]);
  }else if ( strcmp(configuration.command, "min_component") == 0){
    min_component(configuration.filenames[0], configuration.arguments[0][0]);
  }
  else if ( strcmp(configuration.command, "max_component") == 0){
    max_component(configuration.filenames[0], configuration.arguments[0][0]);
  }
  else if (strcmp(configuration.command, "color_invert") == 0) {
    color_invert(configuration.filenames[0]);
} else if (strcmp(configuration.command, "rotate_acw") == 0) {
    rotate_acw(configuration.filenames[0]);
}else if (strcmp(configuration.command, "rotate_cw") == 0) {
    rotate_cw(configuration.filenames[0]);
}else if (strcmp(configuration.command, "mirror_horizontal") == 0) {
    mirror_horizontal(configuration.filenames[0]);
}else if (strcmp(configuration.command, "mirror_vertical") == 0) {
    mirror_vertical(configuration.filenames[0]);
}else if (strcmp(configuration.command, "mirror_total") == 0) {
    mirror_total(configuration.filenames[0]);
} else if (strcmp(configuration.command, "scale_bilinear") == 0) {

  float scale = atof(configuration.arguments[0]);
  scale_bilinear(configuration.filenames[0],scale);

}else if (strcmp(configuration.command, "scale_crop") == 0) {
    
    int center_x = atoi(configuration.arguments[0]);
    int center_y = atoi(configuration.arguments[1]);
    int width    = atoi(configuration.arguments[2]);
    int height   = atoi(configuration.arguments[3]);
 
    scale_crop(configuration.filenames[0], center_x, center_y, width, height);
} else if (strcmp(configuration.command, "stat_report") == 0) {
      stat_report(configuration.filenames[0]);
}




  /*
   * TO COMPLETE
   */
  
  return 0;
  
}

