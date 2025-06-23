contato *find_by_name(const &string name) {
  find_by_name_recursive(agenda.raiz, name);
}

contato *find_by_name_recursive(no *curr, const &string name) {
  char l = name[0];

  if (curr.letra < l) {
    find_by_name_recursive(curr->esq, name);
  } else if (curr.letra > l) {
    find_by_name_recursive(curr->dir, name);
  } else {
    find_by_name_in_lista(curr.lista.p, name);
  }
}

contato *find_by_name_in_lista(celula *c, const &string name) {
  if (strcmp(name, c.pessoa.get_nome()) == 0)
    return c.pessoa;
  else if (c.prox != NULL)
    find_by_name_in_lista(c.prox, name);
  else
    return NULL;
}

