(() => {
  const xhr = new XMLHttpRequest();
  xhr.open("GET", "../data/data.json");
  xhr.addEventListener("load", function() {
    let id = Number(location.href.split("=")[1]) - 1;
    const data = JSON.parse(xhr.response);
    const category = data[id];
    document.getElementById("title").innerHTML = category.category;
    document.getElementById("content2").innerHTML = `
    <div>
      <img src="${category.image}" style="max-width:200px; max-height:200px">
    </div>
    <div>
      <h2 class="d-none d-md-block">${category.title}</h2>
      <p class="text-muted fs-3">$${category.price}</p>
      <p class="text-sm text-wrap">${category.description}</p>
      <div>
        <span class="fw-bolder fs-5">Color: </span>
        <button class="btn btn-outline-dark">red</button>
        <button class="btn btn-outline-dark">gray</button>
        <button class="btn btn-outline-dark">blue</button>
        <button class="btn btn-outline-dark">black</button>
      </div>
      <p class="fs-5 fw-bolder">Category: <span class="fs-6">${category.category}</span></p>
    </div>
  `;
  });
  xhr.send();

  // Display username if find.
  document.getElementById("account-name").innerHTML = `<i class="bi bi-person-fill"></i> ${sessionStorage.user || ""}`;

  // Insert product info to modal.
  const carts = JSON.parse(sessionStorage.carts || "[]");
  document.getElementById("count-cart").textContent = carts.length;
  document.querySelector(".modal-body").innerHTML = "";
  for (const cart of carts) {
    document.querySelector(".modal-body").innerHTML += `
    <div class="mb-4">
      <img src="${cart.image}" class="img-thumbnail w-25" alt="Cinque Terre">
      <span class="text-uppercase">It's ready now <span class="ms-5">${cart.price}<span></span>
    </div>
    `;
  }
})();
