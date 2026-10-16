// Import our custom CSS
import "../scss/styles.scss";

// Import all of Bootstrap's JS
import * as bootstrap from "bootstrap";

import axios, { isCancel, AxiosError } from "axios";

const instance = axios.create({
  baseURL: "http://localhost:8000",
  timeout: 3000,
});

const modal = new bootstrap.Modal(document.getElementById("modal"));

document.querySelector("#modal .btn-close").addEventListener("click", () => {
  modal.hide();
});

document.querySelector("#modal .btn-primary").addEventListener("click", () => {
  modal.hide();
});

document.querySelector("#button-add").addEventListener("click", async () => {
  const nome = document.querySelector("#input-nome").value;
  const categoria = document.querySelector("#input-categoria").value;
  const preco = document.querySelector("#input-preco").value;
  let precoFloat = parseFloat(preco);
  console.log(isNaN(precoFloat));

  const error_title = "error";
  let error_text = "";

  if (nome == "") {
    error_text = "Preencha o input de nome!";
  } else if (categoria == "") {
    error_text = "Preencha o input de categoria!";
  } else if (preco == "") {
    error_text = "Preencha o input de preço!";
  } else if (isNaN(precoFloat)) {
    error_text = "Preço precisa ser um valor numérico!";
  }

  if (error_text) {
    showModal(error_title, error_text);
    return;
  }

  try {
    const response = await instance.post("/produtos", {
      nome,
      categoria,
      preco: precoFloat,
    });

    clearProductTable();
    await reloadProducts();
  } catch (error) {
    showModal(error_title, error.message);
  }
});

function clearProductTable() {
  document.querySelector("#product-table tbody").innerHTML = "";
}

function setDeleteFunctionOnButton(button, id) {
  id = parseInt(id);

  button.addEventListener("click", async () => {
    try {
      await instance.delete(`/produtos/${id}`);
      await reloadProducts();
    } catch (error) {
      showModal("Error", error.message);
    }
  });
}

function setUpdateFunctionOnButton(
  button,
  tdName,
  tdCategoria,
  tdPreco,
  tdButtons,
  id
) {
  id = parseInt(id);

  button.addEventListener("click", async () => {
    try {
      // await instance.put(`/produtos/${id}`, {

      // });
      // await reloadProducts();
      const inputName = document.createElement("input");
      inputName.type = "text";
      inputName.placeholder = "Nome";
      inputName.value = tdName.innerText
      const inputCategoria = document.createElement("input");
      inputCategoria.type = "text";
      inputCategoria.placeholder = "Categoria";
      inputCategoria.value = tdCategoria.innerText
      const inputPreco = document.createElement("input");
      inputPreco.value = tdPreco.innerText
      inputPreco.type = "text";
      inputPreco.placeholder = "Preço";

      tdName.innerHTML = "";
      tdCategoria.innerHTML = "";
      tdPreco.innerHTML = "";

      tdName.appendChild(inputName);
      tdCategoria.appendChild(inputCategoria);
      tdPreco.appendChild(inputPreco);

      const buttonClone = button.cloneNode(true)
      button.parentNode.removeChild(button)
      tdButtons.prepend(buttonClone)
      buttonClone.addEventListener("click", async () => {
        const nome = inputName.value;
        const categoria = inputCategoria.value;
        const preco = inputPreco.value;
        let precoFloat = parseFloat(preco);

        const error_title = "error";
        let error_text = "";

        if (nome == "") {
          error_text = "Preencha o input de nome!";
        } else if (categoria == "") {
          error_text = "Preencha o input de categoria!";
        } else if (preco == "") {
          error_text = "Preencha o input de preço!";
        } else if (isNaN(precoFloat)) {
          error_text = "Preço precisa ser um valor numérico!";
        }

        if (error_text) {
          showModal(error_title, error_text);
          return;
        }

        try {
          console.log(precoFloat)
          const response = await instance.put(`/produtos/${id}`, {
            nome,
            categoria,
            preco: precoFloat,
          });

          clearProductTable();
          await reloadProducts();
        } catch (error) {
          showModal(error_title, error.message);
        }
      })
    } catch (error) {
      showModal("Error", error.message);
    }
  });
}

function addProductToTable(id, name, category, price) {
  const tr = document.createElement("tr");
  tr.id = `product-${id}`;

  const tdID = document.createElement("td");
  tdID.innerText = String(id);
  const tdName = document.createElement("td");
  tdName.innerText = String(name);
  const tdCategory = document.createElement("td");
  tdCategory.innerText = String(category);
  const tdPrice = document.createElement("td");
  tdPrice.innerText = String(price);

  const tdButtons = document.createElement("td");
  tdButtons.style.width = "15%";

  const btnEdit = document.createElement("button");
  setUpdateFunctionOnButton(btnEdit, tdName, tdCategory, tdPrice, tdButtons, id);
  btnEdit.innerText = "📝";
  btnEdit.classList = "btn btn-outline-primary m-1";
  const btnDelete = document.createElement("button");
  setDeleteFunctionOnButton(btnDelete, id);
  btnDelete.innerText = "🗑️";
  btnDelete.classList = "btn btn-outline-danger";

  tdButtons.appendChild(btnEdit);
  tdButtons.appendChild(btnDelete);

  tr.appendChild(tdID);
  tr.appendChild(tdName);
  tr.appendChild(tdCategory);
  tr.appendChild(tdPrice);
  tr.appendChild(tdButtons);

  document.querySelector("#product-table tbody").appendChild(tr);
}

function showModal(title, body) {
  document.querySelector("#modal .modal-title").innerText = title;
  document.querySelector("#modal .modal-body").innerText = body;
  new bootstrap.Modal(document.getElementById("modal")).show();
}

async function setMaxProductClass() {
  try {
    const result = await instance.get("/produtos/max-price");

    document.querySelector(`#product-${result.data.data.id}`).className =
      "table-danger";
  } catch (error) { }
}

async function setMinProductClass() {
  try {
    const result = await instance.get("/produtos/min-price");

    document.querySelector(`#product-${result.data.data.id}`).className =
      "table-success";
  } catch (error) { }
}

async function setMeanProducts() {
  try {
    const result = await instance.get("/produtos/mean");

    document.querySelector(
      "#tr-mean"
    ).innerText = `Preço (${result.data.data.toFixed(2)})`;
  } catch (error) {
  }
}

async function reloadProducts() {
  try {
    clearProductTable();
    const result = await instance.get("/produtos");
    for (const product of result.data.data) {
      addProductToTable(
        product.id,
        product.nome,
        product.categoria,
        product.preco
      );
    }
    await setMaxProductClass();
    await setMinProductClass();
    await setMeanProducts();
  } catch (error) {
    showModal("Error", error.message);
  }
}

await reloadProducts();
