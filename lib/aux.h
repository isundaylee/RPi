#pragma once

void aux_mu_init();
void aux_mu_send(char c);
void aux_mu_send_string(char *str);
void aux_mu_send_uint(unsigned int i);
void aux_mu_send_int(int i);
void aux_mu_send_newline();
char aux_mu_receive();
void aux_mu_flush();
