/*
** EPITECH PROJECT, 2017
** Project bsq Testing
** File description:
** Unit Testing Project bsq
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <ctype.h>
#include "main.h"

void main_redirect_stdout(void)
{
	cr_redirect_stdout();
}

Test(bsq, Return_Value_Test)
{
	cr_assert_eq("Function to test()", "Int Output..");
}

Test(bsq, Stdout_Value_Test, .init = main_redirect_stdout)
{
	cr_assert_stdout_eq_str("Str Output..");
}
