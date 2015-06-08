
#ifdef RHOCK_NATIVE_SYMBOLS
struct rhock_native_symbol rhock_native_symbols[RHOCK_NATIVE_MAX];
int rhock_native_symbols_count = 0;

void rhock_native_symbol_register(const char *name, uint8_t id)
{
    rhock_native_symbols[rhock_native_symbols_count].name = name;
    rhock_native_symbols[rhock_native_symbols_count].id = id;
    rhock_native_symbols_count++;
}
#endif
