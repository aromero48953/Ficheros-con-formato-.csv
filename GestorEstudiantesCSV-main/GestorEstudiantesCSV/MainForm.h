#pragma once

namespace GestorEstudiantesCSV {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;

    public ref class MainForm : public System::Windows::Forms::Form
    {
    public:
        MainForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~MainForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::DataGridView^ tablaDatos;
        System::Windows::Forms::Button^ btnCargar;
        System::Windows::Forms::Button^ btnOrdenar;
        System::Windows::Forms::ComboBox^ cmbCampos;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void)
        {
            this->tablaDatos = (gcnew System::Windows::Forms::DataGridView());
            this->btnCargar = (gcnew System::Windows::Forms::Button());
            this->btnOrdenar = (gcnew System::Windows::Forms::Button());
            this->cmbCampos = (gcnew System::Windows::Forms::ComboBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tablaDatos))->BeginInit();
            this->SuspendLayout();

            // 
            // tablaDatos
            // 
            this->tablaDatos->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->tablaDatos->Location = System::Drawing::Point(12, 55);
            this->tablaDatos->Name = L"tablaDatos";
            this->tablaDatos->Size = System::Drawing::Size(600, 290);
            this->tablaDatos->TabIndex = 0;
            this->tablaDatos->AllowUserToAddRows = false;

            this->tablaDatos->ColumnCount = 5;
            this->tablaDatos->Columns[0]->Name = L"Nombre";
            this->tablaDatos->Columns[1]->Name = L"Apellido Paterno";
            this->tablaDatos->Columns[2]->Name = L"Apellido Materno";
            this->tablaDatos->Columns[3]->Name = L"Matrícula";
            this->tablaDatos->Columns[4]->Name = L"CURP";

            // 
            // btnCargar
            // 
            this->btnCargar->Location = System::Drawing::Point(12, 12);
            this->btnCargar->Name = L"btnCargar";
            this->btnCargar->Size = System::Drawing::Size(120, 30);
            this->btnCargar->TabIndex = 1;
            this->btnCargar->Text = L"Cargar Archivo CSV";
            this->btnCargar->UseVisualStyleBackColor = true;
            this->btnCargar->Click += gcnew System::EventHandler(this, &MainForm::btnCargar_Click);

            // 
            // cmbCampos
            // 
            this->cmbCampos->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->cmbCampos->FormattingEnabled = true;
            this->cmbCampos->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
                L"Nombre", L"Apellido paterno", L"Apellido materno", L"Matrícula", L"CURP"
            });
            this->cmbCampos->Location = System::Drawing::Point(330, 16);
            this->cmbCampos->Name = L"cmbCampos";
            this->cmbCampos->Size = System::Drawing::Size(150, 24);
            this->cmbCampos->TabIndex = 2;

            // 
            // btnOrdenar
            // 
            this->btnOrdenar->Location = System::Drawing::Point(492, 12);
            this->btnOrdenar->Name = L"btnOrdenar";
            this->btnOrdenar->Size = System::Drawing::Size(120, 30);
            this->btnOrdenar->TabIndex = 3;
            this->btnOrdenar->Text = L"Ordenar Datos";
            this->btnOrdenar->UseVisualStyleBackColor = true;
            // AQUI CONECTAMOS EL BOTON DE ORDENAR
            this->btnOrdenar->Click += gcnew System::EventHandler(this, &MainForm::btnOrdenar_Click);

            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(624, 361);
            this->Controls->Add(this->btnOrdenar);
            this->Controls->Add(this->cmbCampos);
            this->Controls->Add(this->btnCargar);
            this->Controls->Add(this->tablaDatos);
            this->Name = L"MainForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Gestor de Estudiantes";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->tablaDatos))->EndInit();
            this->ResumeLayout(false);
        }
#pragma endregion

        // FUNCION PARA CARGAR EL ARCHIVO
    private: System::Void btnCargar_Click(System::Object^ sender, System::EventArgs^ e) {
        OpenFileDialog^ dialog = gcnew OpenFileDialog();
        dialog->Filter = "Archivos CSV (*.csv)|*.csv";
        dialog->Title = "Selecciona el archivo de la tarea";

        if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
            try {
                
                StreamReader^ lector = gcnew StreamReader(dialog->FileName);
                String^ linea = lector->ReadLine();

                tablaDatos->Rows->Clear();

                while ((linea = lector->ReadLine()) != nullptr) {
                    array<String^>^ datos = linea->Split(',');
                    if (datos->Length >= 5) {
                        tablaDatos->Rows->Add(datos[0], datos[1], datos[2], datos[3], datos[4]);
                    }
                }
                lector->Close();
                MessageBox::Show("¡Archivo cargado con éxito!", "Todo correcto", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            catch (Exception^ ex) {
                MessageBox::Show("Hubo un error al leer el archivo: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }
    }

           // FUNCION PARA ORDENAR LOS DATOS 
    private: System::Void btnOrdenar_Click(System::Object^ sender, System::EventArgs^ e) {
        if (cmbCampos->SelectedIndex == -1) {
            MessageBox::Show("Por favor, selecciona por qué campo quieres ordenar usando la lista desplegable.", "Aviso", MessageBoxButtons::OK, MessageBoxIcon::Warning);
            return;
        }

        // Sacamos el número de la opción elegida (0=Nombre, 1=Ap. Paterno, etc.)
        int indiceColumna = cmbCampos->SelectedIndex;

        // Le decimos a la tabla que se ordene por esa columna de la A a la Z (Ascendente)
        tablaDatos->Sort(tablaDatos->Columns[indiceColumna], System::ComponentModel::ListSortDirection::Ascending);
    }

    };
}