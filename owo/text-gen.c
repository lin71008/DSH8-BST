#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef LINE_MAX_CHAR
#define LINE_MAX_CHAR 80
#endif

int main(int argc, char const *argv[])
{
	FILE *fp = fopen("../ui-setting", "r");
	FILE *fop = fopen("../ui.c", "w");
	FILE *fhop = fopen("../ui.h", "w");
	if (fp == NULL || fop == NULL || fhop == NULL) return 1;

	fprintf(fop, "// auto generator by text-gen.exe\n");
	fprintf(fhop, "// auto generator by text-gen.exe\n");

	fprintf(fop, "#include <stdio.h>\n\n");
	fprintf(fop, "#include \"ui.h\"\n\n");

	fprintf(fhop, "#ifndef __UI_H__\n");
	fprintf(fhop, "#define __UI_H__\n\n");

	ssize_t line_size;
	char *line_buffer = NULL;
	size_t line_buffer_size = 0;
	line_size = getline(&line_buffer, &line_buffer_size, fp);

	bool function_begin = false;
	bool function_header_begin = true, function_header_end = false;

	while (line_size >= 0)
	{
		char *token;
		if (line_buffer_size < 0)  // Real Empty Line
		{
			line_size = getline(&line_buffer, &line_buffer_size, fp);
			continue;
		}
		token = strtok(line_buffer, " \t\n");
		if (token == NULL)  // Empty Line (Contain _Space)
		{
			if (function_begin == true)
			{
				fprintf(fop, "}\n\n");
				function_header_end = false;
				function_header_begin = true;
				function_begin = false;
			}
			line_size = getline(&line_buffer, &line_buffer_size, fp);
			continue;
		}
		else if (strcmp(token, "#") == 0)
		{
			fprintf(fop, "void ");
			fprintf(fhop, "extern void ");
			token = strtok(NULL, " \t\n");
			while (token != NULL)
			{
				fprintf(fop, "%s", token);
				fprintf(fhop, "%s", token);
				token = strtok(NULL, " \t\n");
			}
			fprintf(fop, "(void)\n{\n");
			fprintf(fhop, "(void);\n");
			function_begin = true;
		}
		else if (strcmp(token, "-") == 0)
		{
			int line_o_size = 0;
			bool first_line = true, first_value = true;
			token = strtok(NULL, " \t\n");
			while (token != NULL)
			{
				if (first_line == true)
				{
					fprintf(fop, "\tprintf(\"");
					first_line = false;
				}
				if (function_header_begin == true)
				{
					fprintf(fop, "=== ");
					function_header_begin = false;
					function_header_end = true;
				}
				if (line_o_size + 1 + strlen(token) <= LINE_MAX_CHAR)
				{
					if (first_value == true)
					{
						fprintf(fop, "%s", token);
						line_o_size = strlen(token);
						first_value = false;
					}
					else
					{
						fprintf(fop, " %s", token);
						line_o_size += 1 + strlen(token);
					}
				}
				else
				{
					fprintf(fop, "\\n\");\n\tprintf(\"%s", token);
					line_o_size = strlen(token);
				}
				token = strtok(NULL, " \t\n");
			}
			if (first_line == false)
			{
				if (function_header_end == true)
				{
					fprintf(fop, " ===");
					function_header_end = false;
				}
				fprintf(fop, "\\n\");\n");
			}
		}
		line_size = getline(&line_buffer, &line_buffer_size, fp);
	}

	if (function_begin == true)
	{
		fprintf(fop, "}\n");
		function_header_end = false;
		function_header_begin = true;
		function_begin = false;
	}

	fprintf(fhop, "\n#endif\n\n");

	fclose(fhop);
	fclose(fop);
	fclose(fp);
	return 0;
}
