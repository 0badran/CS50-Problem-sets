const xhr = new XMLHttpRequest();
xhr.open("GET", "../data/data.json");
xhr.send();
xhr.addEventListener("load", function() {
  const data = JSON.parse(xhr.response);
  let setContent = document.getElementById("content");
  // Logic for sorting all categories
  const allCategories = [
    "men's clothing",
    "women's clothing",
    "electronics",
    "jewelery",
  ];
  for (let category of allCategories) {
    setContent.innerHTML += `<h1 class="display-1 d-i text-muted text-center" id="${category}" style="margin: 100px 0;">${category.toUpperCase()}</h1>`
    data.forEach((ele) => {
      if (category == ele.category) {
        setContent.innerHTML += `
        <div class="col-lg-3 col-md-6 mt-3 text-center" >
        <div class="hoverit">
        <img src="${ele.image}" class="img-thumbnail border-0" style="height: 300px; width:400px"/>
        <a href="#" class="add-to-cart"><span class="text-card">Add Cart <i class="bi bi-cart-plus-fill ms-2"></i></span></a>
        </div>
        <button onclick="productDetails(${ele.id})" class="btn btn-outline-dark rounded-0">Buy</button>
        <p class="font-monospace">${ele.title} <span class="text-secondary fs-3" >${ele.price}$</span></p>
        </div>
        `;
      }
    });
  }

  (() => {
    // Display username if find.
    document.getElementById("account-name").innerHTML = `<i class="bi bi-person-fill"></i> ${sessionStorage.user || ""}`;

    // Insert product info to modal
    function modalInfo() {
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
    }
    modalInfo();

    // if the element clicked that contains add-to-cart class!.
    const allItems = document.querySelectorAll(".add-to-cart");
    for (let item of allItems) {
      item.addEventListener("click", function() {
        const myArray = sessionStorage.carts ? JSON.parse(sessionStorage.carts) : [];
        myArray.push({ image: item.parentNode.children[0].src, price: item.parentNode.parentNode.children[2].children[0].innerHTML })
        // Iam use sessionStorage to store data!.
        const myCarts = JSON.stringify(myArray);
        sessionStorage.setItem('carts', myCarts);
        // call modal info when update cart.
        modalInfo();
      });
    }
  })();
});

function productDetails(id) {
  location.href = "./product-details.html?id=" + id;
}
