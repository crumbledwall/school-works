<template>
  <div id="app">
    <div class="header">
      <h2 class="logo">REGE HERE</h2>
    </div>
    <div class="register">
      <el-card>
        <h2>REGISTER</h2>
        <el-form
          ref="form"
          class="register-form"
          :model="model"
          :rules="rules"
          @submit.prevent="register"
        >
          <el-form-item prop="email">
            <el-input
              v-model="model.email"
              placeholder="email"
              prefix-icon="fas fa-user"
            />
          </el-form-item>
          <el-form-item prop="password">
            <el-input
              v-model="model.password"
              placeholder="Password"
              type="password"
              prefix-icon="fas fa-lock"
            />
          </el-form-item>
          <el-form-item>
            <el-button
              :loading="loading"
              class="register-button"
              type="primary"
              native-type="submit"
              block
              >register</el-button
            >
          </el-form-item>
        </el-form>
      </el-card>
    </div>
  </div>
</template>

<script>
export default {
  name: "Register",
  data() {
    return {
      validCredentials: {
        email: "lightscope",
        password: "lightscope",
      },
      model: {
        email: "",
        password: "",
      },
      loading: false,
      rules: {
        email: [
          {
            required: true,
            message: "email is required",
            trigger: "blur",
          },
          {
            min: 4,
            message: "email length should be at least 5 characters",
            trigger: "blur",
          },
        ],
        password: [
          { required: true, message: "Password is required", trigger: "blur" },
          {
            min: 5,
            message: "Password length should be at least 5 characters",
            trigger: "blur",
          },
        ],
      },
    };
  },
  methods: {
    register() {
      this.$refs["form"].validate((valid) => {
        if (valid) {
          this.loading = true;
          this.$store.dispatch("user/register", this.model).then((res) => {
            this.$router.push({ path: "/" });
          });
          this.loading = false;
        } else {
          console.log("error submit!!");
          return false;
        }
      });
    },
  },
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
.register {
  flex: 1;
  display: flex;
  justify-content: center;
  align-items: center;
}

.register-button {
  width: 100%;
  margin-top: 40px;
}
.register-form {
  width: 290px;
}
.forgot-password {
  margin-top: 10px;
}

.register .el-input__prefix {
  background: rgb(238, 237, 234);
  left: 0;
  height: calc(100% - 2px);
  left: 1px;
  top: 1px;
  border-radius: 3px;
}
.register .el-input input {
  padding-left: 35px;
}
.register .el-card {
  padding-top: 0;
  padding-bottom: 30px;
}
h2 {
  font-family: "Open Sans";
  letter-spacing: 1px;
  font-family: Roboto, sans-serif;
  padding-bottom: 20px;
}

.register .el-card {
  width: 340px;
  display: flex;
  justify-content: center;
}
#app {
  font-family: Roboto, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin: 0;
  display: flex;
  flex-direction: column;
  min-height: 100vh;
}
body {
  margin: 0;
  padding: 0;
  background: #102a43;
  background-size: contain;
}
.footer,
.header {
  padding: 20px 20px;
  color: #f0f4f8;
  display: flex;
  flex-direction: column;
  align-items: center;
}

h1,
h2,
h3 {
  color: #f0f4f8;
  padding: 0;
  margin: 0;
}
h2 {
  color: #b0b3b5;
}
.links {
  display: flex;
  font-family: "Open Sans";
}
.links span {
  padding: 0 10px;
  font-size: 18px;
  border-right: 1px solid #9fb3c8;
}
.version {
  font-family: "Open Sans";
  padding: 0 10px;
  color: #9fb3c8;
  font-size: 12px;
  margin-top: 5px;
}

.header {
  padding: 10px 20px;
}
.header .logo {
  font-family: "Open Sans";
  letter-spacing: 3px;
  padding-top: 15px;
  padding-bottom: 15px;
}
.header .logo .part-2 {
  color: #d64545;
}
</style>
