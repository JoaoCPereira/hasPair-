import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Função que lê os dados de um arquivo CSV e retorna um DataFrame do pandas.
def load_data(file_path):
    df = pd.read_csv(file_path, sep=',\s*', engine='python')
    return df

# Função que filtra os dados com base nas condições especificadas.
# Retorna o DataFrame filtrado.
def filter_data_by_case(df, case):
    # Filtrar por nome de função
    df_filtered = df[df['Nome função'].isin([
        'hasPairSum', 
        'hasPairSumThreads', 
        'hasPairSumSorted', 
        'hasPairSumSortedBinarySearch', 
        'hasPairSumSortedBinarySearchThreads'
    ])]

    # Filtrar por caso específico
    df_filtered = df_filtered[df_filtered['Caso'] == case]

    # Remover os 5 melhores e 5 piores resultados para cada função
    df_filtered = df_filtered.groupby('Nome função', group_keys=False).apply(lambda x: x.nsmallest(len(x) - 5, 'Tempo execução (nanosegundos)'))
    df_filtered = df_filtered.groupby('Nome função', group_keys=False).apply(lambda x: x.nlargest(len(x) - 5, 'Tempo execução (nanosegundos)')).reset_index(drop=True)

    return df_filtered

# Plota o tempo de execução das funções a partir do DataFrame filtrado e salva como PNG.
def plot_execution_time(df, case):
    plt.figure(figsize=(12, 8))
    sns.set_theme(style="darkgrid")

    # Plot das respostas para diferentes eventos e regiões
    ax = sns.lineplot(
        x="Tamanho vector",
        y="Tempo execução (nanosegundos)",
        hue="Nome função",
        data=df,
        errorbar='sd',  # erro como desvio padrão
        palette=sns.color_palette("Set2", n_colors=df['Nome função'].nunique()),  # ajuste na paleta
        marker='o'
    )

    plt.title(f'Tempo de execução das funções - {case}')
    plt.xlabel('Tamanho vector')
    plt.ylabel('Tempo de Execução (nanosegundos)')

    # Save the plot as a PNG file
    filename = f'img/execution_time_{case.replace(" ", "_").replace("(", "").replace(")", "").replace("!", "N")}.png'
    plt.savefig(filename, bbox_inches='tight')

    plt.ylabel('Tempo de Execução logarítmico (nanosegundos)')
    ax.set_yscale("log")
    
    # Save the plot as a PNG file
    filename = f'img/execution_time_{case.replace(" ", "_").replace("(", "").replace(")", "").replace("!", "N")}_log.png'
    plt.savefig(filename, bbox_inches='tight')
    plt.close()

# Função para gerar e salvar a tabela como imagem PNG.
def save_table_as_png(df, case, vector_sizes):

    # Filtra o DataFrame pelos tamanhos de vetor especificados
    df_filtered = df[df['Tamanho vector'].isin(vector_sizes)]

    # Seleciona apenas as colunas necessárias para a tabela e converte para milissegundos
    table_data = df_filtered.groupby('Nome função').agg({'Tempo execução (nanosegundos)': ['mean', 'std']})
    table_data.columns = ['Média', 'Desvio Padrão (ms)']
    table_data /= 1_000_000  # Converte de nanosegundos para milissegundos
    
    # Formata as informações na mesma coluna
    table_data['Média ± Desvio (ms)'] = table_data.apply(
        lambda row: f"{row['Média']:.2f} ± {row['Desvio Padrão (ms)']:.2f}", axis=1
    )
    
    # Apenas a coluna final
    table_data = table_data[['Média ± Desvio (ms)']].reset_index()

    # Cria uma figura para a tabela com tamanho aumentado
    fig, ax = plt.subplots(figsize=(12, 4))  # Tamanho maior para a tabela
    ax.axis('tight')
    ax.axis('off')
    
    # Adiciona a tabela à figura, com altura de linha ajustada
    table = ax.table(cellText=table_data.values, colLabels=table_data.columns, cellLoc='center', loc='center')
    
    # Ajusta a altura das linhas
    for cell in table.get_celld().values():
        cell.set_height(0.2)  # Altera o valor conforme necessário para ajustar o espaço das linhas

    # Salva a tabela como um arquivo PNG
    filename = f'img/execution_time_table{vector_sizes}-_{case.replace(" ", "_").replace("(", "").replace(")", "").replace("!", "N")}.png'
    plt.savefig(filename, bbox_inches='tight')
    plt.close()

def main():
    # Caminho para o ficheiro de dados
    file_path = '../new_[N32768_32767]_output_500.txt'

    # Leitura do ficheiro
    df = load_data(file_path)

    # Lista de casos para gerar gráficos
    casos = [
        "Pior caso x !C A",
        "Melhor Caso BF (A[0] + A[1] == x)"
    ]

    for caso in casos:
        # Filtrar os dados por cada caso
        df_filtered = filter_data_by_case(df, caso)

        # Visualização dos primeiros registros
        print(f"Primeiros registros para o caso: {caso}")
        print(df_filtered.head())

        # Plotar e salvar o gráfico para cada caso
        plot_execution_time(df_filtered, caso)

        # Salvar a tabela como uma imagem PNG
        save_table_as_png(df_filtered, caso, [2097152])
        save_table_as_png(df_filtered, caso, [32768])
        save_table_as_png(df_filtered, caso, [131072])

if __name__ == "__main__":
    main()
