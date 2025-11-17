#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
using namespace std;


class Produto {
public:
    string nome;
    string categoria;
    double preco;
    int estoque;

    Produto(string n, string c, double p, int e)
        : nome(n), categoria(c), preco(p), estoque(e) {}
};



class Inventario {
private:
    vector<Produto> produtos;      // Lista de produtos
    set<string> categorias;        // Categorias
    list<Produto> historicoVendas; // Histórico de vendas

public:

    
    void adicionarProduto(const Produto& p) {
        produtos.push_back(p);
        categorias.insert(p.categoria);
    }

   
    Produto* buscarProduto(const string& nome) {
        for (auto& p : produtos) {
            if (p.nome == nome) return &p;
        }
        return nullptr;
    }

   
    void listarPorCategoria(const string& cat) {
        cout << "\nProdutos da categoria: " << cat << "\n";
        for (const auto& p : produtos) {
            if (p.categoria == cat) {
                cout << " - " << p.nome << " | Preço: " << p.preco
                     << " | Estoque: " << p.estoque << "\n";
            }
        }
    }

    
    double valorTotalInventario() const {
        double total = 0;
        for (const auto& p : produtos)
            total += p.preco * p.estoque;
        return total;
    }

    
    bool registrarVenda(const string& nome, int quantidade) {
        Produto* p = buscarProduto(nome);
        if (!p) {
            cout << "Produto não encontrado!\n";
            return false;
        }
        if (p->estoque < quantidade) {
            cout << "Estoque insuficiente!\n";
            return false;
        }

        p->estoque -= quantidade;

        // Adiciona ao histórico
        for (int i = 0; i < quantidade; i++)
            historicoVendas.push_back(*p);

        cout << "Venda registrada!\n";
        return true;
    }

   
    void mostrarHistorico() {
        cout << "\n=== Histórico de Vendas ===\n";
        for (const auto& p : historicoVendas) {
            cout << "Produto: " << p.nome
                 << " | Categoria: " << p.categoria
                 << " | Preço: " << p.preco << "\n";
        }
    }

  
    void mostrarCategorias() {
        cout << "\n=== Categorias ===\n";

        // Recalcula contagens e totais corretamente
        map<string, int> contagem;
        map<string, double> totalValor;

        for (const auto& p : produtos) {
            contagem[p.categoria]++;
            totalValor[p.categoria] += p.preco * p.estoque;
        }

        for (const auto& cat : categorias) {
            cout << cat
                 << " | Quantidade: " << contagem[cat]
                 << " | Valor total: R$ " << totalValor[cat]
                 << "\n";
        }
    }
};



// Programa Principal
int main() {
    Inventario loja;

    loja.adicionarProduto(Produto("Mouse", "Periféricos", 80.0, 15));
    loja.adicionarProduto(Produto("Teclado", "Periféricos", 150.0, 10));
    loja.adicionarProduto(Produto("Monitor", "Video", 900.0, 5));
    loja.adicionarProduto(Produto("HD 1TB", "Armazenamento", 250.0, 7));

    loja.listarPorCategoria("Periféricos");

    cout << "\nValor total do inventário: R$ "
         << loja.valorTotalInventario() << "\n";

    loja.registrarVenda("Mouse", 3);
    loja.registrarVenda("Monitor", 1);

    loja.mostrarHistorico();
    loja.mostrarCategorias();

    return 0;
}
