#!/usr/bin/env python3

import sys
import argparse
import re
import os

PATH_TO_TEST_TYPE_ARG="path-to-test-type-header"
OUTDIR_ARG="out-directory"

GENERATED_FILE="TestTypesInclude.h"
BASE_T = 50
PART_TWO_PER_LINE = 14

INTERNAL_ONE_TAG = "$INTERNAL_ONE"
INTERNAL_TWO_TAG = "$INTERNAL_TWO"
BIG_TYPE_TAG = "$BIG_TYPE"

FILE_TEMPLATE = f"""// THIS HEADER IS AUTOGENERATED! PLEASE DO NOT EDIT
#ifndef TEST_TYPES_INCLUDE
#define TEST_TYPES_INCLUDE

#include <gtest/gtest.h>

/*
 * Note lcarlier:
 * Google test supports maximum 50 different classes when running class templated
 * UT. I have UT that have more than 50 classes so I extend Google test
 * here.
 * Note that I didn't understand how this works. I just copied/pasted the
 * needed part Google of the header file and extended the parameters.
 * I had to create a new type (BigTypes) because it is not possible to
 * redefine the initial Google type "::testing::internal::Types"
 * with more than 50 template parameters.
 */
namespace testing
{{
  namespace internal
  {{
    {INTERNAL_ONE_TAG}
  }} //namespace internal
  {BIG_TYPE_TAG}
  namespace internal
  {{
    {INTERNAL_TWO_TAG}
  }} //namespace internal
}} //namespace testing
#endif /*TEST_TYPES_INCLUDE*/
"""

def get_arg(args, key):
    return getattr(args, key.replace("-","_"))

def main():
    args, _ = parse_arguments()
    path_to_test_type = get_arg(args, PATH_TO_TEST_TYPE_ARG)
    out_dir = get_arg(args, OUTDIR_ARG)
    generate_test_type(path_to_test_type, out_dir)
    return 0

def get_number_of_factories(path_to_test_type):
    # e.g UnsIntFunVoidFactory
    REGEX_FACTORY = "^\s+[A-Za-z0-9]+Factory"
    nb_factories = 0
    with open(path_to_test_type, "r") as f:
        all_lines = f.readlines()
        for line in all_lines:
            if line is None:
                return
            m = re.match(REGEX_FACTORY, line)
            if m:
                nb_factories += 1
    print(f"{nb_factories} factories found.")
    return nb_factories

def generate_template_part(n):
    TEMPLATE_PART_PER_LINE = 5
    template_part="""template <typename T1, typename T2, typename T3, typename T4, typename T5,
        typename T6, typename T7, typename T8, typename T9, typename T10,
        typename T11, typename T12, typename T13, typename T14, typename T15,
        typename T16, typename T17, typename T18, typename T19, typename T20,
        typename T21, typename T22, typename T23, typename T24, typename T25,
        typename T26, typename T27, typename T28, typename T29, typename T30,
        typename T31, typename T32, typename T33, typename T34, typename T35,
        typename T36, typename T37, typename T38, typename T39, typename T40,
        typename T41, typename T42, typename T43, typename T44, typename T45,
        typename T46, typename T47, typename T48, typename T49, typename T50"""
    template_cr = 5
    nb_t_to_generate = n - BASE_T
    for t in range(nb_t_to_generate):
        current_t = t + BASE_T + 1
        template_part += ","
        if (template_cr % TEMPLATE_PART_PER_LINE) == 0:
            template_part += "\n        "
        else:
            template_part += " "
        template_part += f"typename T{current_t}"
        template_cr += 1
    template_part += ">"
    return template_part

def generate_internal_one(n):
    part_one=generate_template_part(n)
    part_two=f"""
    struct Types{n} {{
      typedef T1 Head;
      //Types{n - 1} takes {n - 1} arguments from T2 to T{n}
      typedef Types{n - 1}<T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13, T14, T15,
          T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29,
          T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
          T44, T45, T46, T47, T48, T49, T50"""
    part_two_cr = 7
    nb_t_to_generate = n - BASE_T
    for t in range(nb_t_to_generate):
        current_t = t + BASE_T + 1
        part_two += ","
        if (part_two_cr % PART_TWO_PER_LINE) == 0:
            part_two += "\n          "
        else:
            part_two += " "
        part_two += f"T{current_t}"
        part_two_cr += 1
    part_two += """> Tail;
    };

    """
    return part_one + part_two

def generate_internal_two(n):
    part_one=part_one=generate_template_part(n)
    part_two="""
    struct TypeList<BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, T13,
        T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26, T27, T28,
        T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40, T41, T42, T43,
        T44, T45, T46, T47, T48, T49, T50"""
    part_two_cr = 7
    part_three=""" > {
      typedef typename BigTypes<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
          T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
          T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
          T41, T42, T43, T44, T45, T46, T47, T48, T49, T50"""
    part_three_cr = 10
    nb_t_to_generate = n - BASE_T
    for t in range(nb_t_to_generate):
        current_t = t + BASE_T + 1
        part_two += ","
        part_three += ","
        if (part_two_cr % PART_TWO_PER_LINE) == 0:
            part_two += "\n        "
        else:
            part_two += " "
        if (part_three_cr % PART_TWO_PER_LINE) == 0:
            part_three += "\n          "
        else:
            part_three += " "
        part_two += f"T{current_t}"
        part_three += f"T{current_t}"
        part_two_cr += 1
        part_three_cr += 1
    part_two += ">"
    part_three += """>::type type;
    };

    """
    return part_one + part_two + part_three

def generate_big_type(n):
    PART_ONE_PER_LINE=2
    part_one="""template <typename T1 = internal::None, typename T2 = internal::None,
      typename T3 = internal::None, typename T4 = internal::None,
      typename T5 = internal::None, typename T6 = internal::None,
      typename T7 = internal::None, typename T8 = internal::None,
      typename T9 = internal::None, typename T10 = internal::None,
      typename T11 = internal::None, typename T12 = internal::None,
      typename T13 = internal::None, typename T14 = internal::None,
      typename T15 = internal::None, typename T16 = internal::None,
      typename T17 = internal::None, typename T18 = internal::None,
      typename T19 = internal::None, typename T20 = internal::None,
      typename T21 = internal::None, typename T22 = internal::None,
      typename T23 = internal::None, typename T24 = internal::None,
      typename T25 = internal::None, typename T26 = internal::None,
      typename T27 = internal::None, typename T28 = internal::None,
      typename T29 = internal::None, typename T30 = internal::None,
      typename T31 = internal::None, typename T32 = internal::None,
      typename T33 = internal::None, typename T34 = internal::None,
      typename T35 = internal::None, typename T36 = internal::None,
      typename T37 = internal::None, typename T38 = internal::None,
      typename T39 = internal::None, typename T40 = internal::None,
      typename T41 = internal::None, typename T42 = internal::None,
      typename T43 = internal::None, typename T44 = internal::None,
      typename T45 = internal::None, typename T46 = internal::None,
      typename T47 = internal::None, typename T48 = internal::None,
      typename T49 = internal::None, typename T50 = internal::None"""
    part_one_cr=2
    part_two=f"""struct BigTypes {{
    typedef internal::Types{n}<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12,
        T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24, T25, T26,
        T27, T28, T29, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39, T40,
        T41, T42, T43, T44, T45, T46, T47, T48, T49, T50"""
    part_two_cr=10
    nb_t_to_generate = n - BASE_T
    for t in range(nb_t_to_generate):
        current_t = t + BASE_T + 1
        part_one += ","
        part_two += ","
        if (part_one_cr % PART_ONE_PER_LINE) == 0:
            part_one += "\n      "
        else:
            part_one += " "
        if (part_two_cr % PART_TWO_PER_LINE) == 0:
            part_two += "\n        "
        else:
            part_two += " "
        part_one += f"typename T{current_t} = internal::None"
        part_two += f"T{current_t}"
        part_one_cr += 1
        part_two_cr += 1
    part_one += """>
  """
    part_two += """> type;
  };"""
    return part_one + part_two

def generate_test_type_inclue(out_dir, nb_factories):
    out_file = f"{out_dir}/{GENERATED_FILE}"
    print(f"Generating {out_file}")
    internal_one = ""
    internal_two = ""
    big_type = generate_big_type(nb_factories)
    with open(out_file, "w") as f:
        nb_t_to_generate = nb_factories - BASE_T
        for t in range(nb_t_to_generate):
            current_t = t + BASE_T + 1
            internal_one += generate_internal_one(current_t)
            internal_two += generate_internal_two(current_t)
        f.write(FILE_TEMPLATE.replace(f"{INTERNAL_ONE_TAG}", internal_one).replace(f"{BIG_TYPE_TAG}", big_type).replace(f"{INTERNAL_TWO_TAG}", internal_two))

def generate_test_type(path_to_test_type, out_dir):
    nb_factories = get_number_of_factories(path_to_test_type)
    generate_test_type_inclue(out_dir, nb_factories)

def check_directory(value):
    if not os.path.isdir(value):
        raise argparse.ArgumentTypeError(f"{value} is not a directory")
    return value

def parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument(f"--{PATH_TO_TEST_TYPE_ARG}", required=True, type=str, help="Path to TestTypes.h")
    parser.add_argument(f"--{OUTDIR_ARG}", required=True, type=check_directory, help=f"Output directory of {GENERATED_FILE}")
    args = parser.parse_args()
    return args, parser

if __name__ == "__main__":
    sys.exit(main())